// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TFGameInstance.h"
#include "Game/TFSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BaseClass/TFActor.h"
#include "BaseClass/TFCharacter.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Logger.h"

UTFGameInstance::UTFGameInstance()
{

}

void UTFGameInstance::CreateSaveSlot()
{
	SaveGameObject = Cast<UTFSaveGame>(UGameplayStatics::CreateSaveGameObject(UTFSaveGame::StaticClass()));
}

void UTFGameInstance::GatherActorDAta()
{
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!IsValid(Actor) || !Actor->Implements<USaveActorInterface>())
		{
			continue;
		}

		ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}

		FGuid SaveAI = Inter->GetActorSaveID_Implementation();
		if (!SaveAI.IsValid())
		{
			continue;
		}
		FSaveActorData SaveAD = Inter->GetSaveData_Implementation();

		FMemoryWriter MemWriter(SaveAD.ByteData);
		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);

		for (auto ActorComp : Actor->GetComponents())
		{
			if (!ActorComp->Implements<USaveActorInterface>())
			{
				continue;
			}

			ISaveActorInterface* CompInter = Cast<ISaveActorInterface>(ActorComp);

			if (CompInter == nullptr)
			{
				continue;
			}
			FSaveComponentsData SaveCD = CompInter->GetComponentSaveData_Implementation();
			FMemoryWriter CompMemWriter(SaveCD.ByteData);
			FObjectAndNameAsStringProxyArchive CAr(CompMemWriter, true);
			CAr.ArIsSaveGame = true;
			ActorComp->Serialize(CAr);
			SaveCD.ComponentClass = ActorComp->GetClass();
			SaveAD.ComponentData.Add(SaveCD);
		}
		SaveableActorData.Add(SaveAI, SaveAD);
	}
	GatherPlayerData();
}

void UTFGameInstance::LoadGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameName, 0))
	{
		Logger::GetInstance()->AddMessage("LoadGame called with invalid save name", ErrorLevel::EL_WARNING);
		return;
	}

	SaveableActorData.Empty();
	SaveGameObject = Cast<UTFSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameName, 0));
	SaveableActorData = SaveGameObject->GetSaveActorData();
	PlayerData = SaveGameObject->GetPlayerData();

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!IsValid(Actor) || !Actor->Implements<USaveActorInterface>())
		{
			continue;
		}	
		ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}
		if (Inter->Execute_GetSaveData(Actor).WasSpawned)
		{
			Actor->Destroy();
		}
	}

	for (TTuple<FGuid, FSaveActorData> SaveAD : SaveableActorData)
	{
		if (SaveAD.Value.WasSpawned)
		{
			UClass* ToSpawnClass = SaveAD.Value.ActorClass;
			if (ToSpawnClass->IsChildOf(ATFCharacter::StaticClass()))
			{
				ATFCharacter* CSpawned = GetWorld()->SpawnActor<ATFCharacter>(ToSpawnClass, SaveAD.Value.ActorTransform);
				ISaveActorInterface* Inter = Cast<ISaveActorInterface>(CSpawned);
				if (Inter == nullptr)
				{
					CSpawned->Destroy();
					continue;
				}
				Inter->Execute_SetActorGuid(CSpawned, SaveAD.Key);
				CSpawned->SetWasSpawned(true);
				continue;
			}

			ATFActor* Spawned = GetWorld()->SpawnActor<ATFActor>(ToSpawnClass, SaveAD.Value.ActorTransform);
			ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Spawned);
			if (Inter == nullptr)
			{
				Spawned->Destroy();
				continue;
			}
			Inter->Execute_SetActorGuid(Spawned, SaveAD.Key);
			Spawned->SetWasSpawned(true);
		}
	}

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!IsValid(Actor) || !Actor->Implements<USaveActorInterface>())
		{
			continue;
		}
		ISaveActorInterface* Inter = Cast<ISaveActorInterface>(Actor);

		if (Inter == nullptr)
		{
			continue;
		}
		FGuid SaveAI = Inter->GetActorSaveID_Implementation();
		if (!SaveableActorData.Find(SaveAI))
		{
			continue;
		}

		FSaveActorData SaveAD = SaveableActorData[SaveAI];
		Actor->SetActorTransform(SaveAD.ActorTransform);

		FMemoryReader MemReader(SaveAD.ByteData);
		FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);
		Inter->Execute_UpdateFromSave(Actor);
		for (auto ActorComp : Actor->GetComponents())
		{
			if (!ActorComp->Implements<USaveActorInterface>())
			{
				continue;
			}

			ISaveActorInterface* CompInter = Cast<ISaveActorInterface>(ActorComp);
			if (CompInter == nullptr)
			{
				continue;
			}
			for (auto SaveCD : SaveAD.ComponentData)
			{
				/* Not Safe if Actor has 2 of the same Components that are saved.
				* As the First Component will get all the data.
				   Option to fix is to maybe use FGuid */

				if (SaveCD.ComponentClass != ActorComp->GetClass())
				{
					continue;
				}
				FMemoryReader CompMemReader(SaveCD.ByteData);
				FObjectAndNameAsStringProxyArchive CAr(CompMemReader, true);
				CAr.ArIsSaveGame = true;
				ActorComp->Serialize(CAr);
				if (SaveCD.RawData.IsEmpty())
				{
					break;
				}
				CompInter->SetComponentSaveData_Implementation(SaveCD);
				break;
			}
		}
	}
	SetPlayerData();
}

void UTFGameInstance::GatherPlayerData()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ISaveActorInterface* Inter = Cast<ISaveActorInterface>(PlayerCharacter);
	if (Inter == nullptr)
	{
		Logger::GetInstance()->AddMessage("UTFGameInstance::GatherPlayerData - Player Character does not implement ISaveActorInterface", ErrorLevel::EL_WARNING);
		return;
	}
	FSaveActorData SaveAD = Inter->GetSaveData_Implementation();
	
	FMemoryWriter MemWriter(SaveAD.ByteData);
	FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
	Ar.ArIsSaveGame = true;
	PlayerCharacter->Serialize(Ar);

	for (auto ActorComp : PlayerCharacter->GetComponents())
	{
		if (!ActorComp->Implements<USaveActorInterface>())
		{
			continue;
		}

		ISaveActorInterface* CompInter = Cast<ISaveActorInterface>(ActorComp);

		if (CompInter == nullptr)
		{
			continue;
		}
		FSaveComponentsData SaveCD = CompInter->GetComponentSaveData_Implementation();
		FMemoryWriter CompMemWriter(SaveCD.ByteData);
		FObjectAndNameAsStringProxyArchive CAr(CompMemWriter, true);
		CAr.ArIsSaveGame = true;
		ActorComp->Serialize(CAr);
		SaveCD.ComponentClass = ActorComp->GetClass();
		SaveAD.ComponentData.Add(SaveCD);
	}
	PlayerData = SaveAD;
}

void UTFGameInstance::SetPlayerData()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ISaveActorInterface* Inter = Cast<ISaveActorInterface>(PlayerCharacter);
	if (Inter == nullptr)
	{
		// Log Error
		return;
	}
	PlayerCharacter->SetActorTransform(PlayerData.ActorTransform);
	FMemoryReader PCMemReader(PlayerData.ByteData);
	FObjectAndNameAsStringProxyArchive Ar(PCMemReader, true);
	Ar.ArIsSaveGame = true;
	PlayerCharacter->Serialize(Ar);

	for (auto ActorComp : PlayerCharacter->GetComponents())
	{
		if (!ActorComp->Implements<USaveActorInterface>())
		{
			continue;
		}

		ISaveActorInterface* CompInter = Cast<ISaveActorInterface>(ActorComp);
		if (CompInter == nullptr)
		{
			continue;
		}
		for (auto SaveCD : PlayerData.ComponentData)
		{
			/* Not Safe if Actor has 2 of the same Components that are saved.
			* As the First Component will get all the data.
			   Option to fix is to maybe use FGuid */

			if (SaveCD.ComponentClass != ActorComp->GetClass())
			{
				continue;
			}
			FMemoryReader CompMemReader(SaveCD.ByteData);
			FObjectAndNameAsStringProxyArchive CAr(CompMemReader, true);
			CAr.ArIsSaveGame = true;
			ActorComp->Serialize(CAr);
			if (SaveCD.RawData.IsEmpty())
			{
				break;
			}
			CompInter->SetComponentSaveData_Implementation(SaveCD);
			break;
		}
	}
}

void UTFGameInstance::AddActorData(const FGuid& ActorID, FSaveActorData ActorData)
{
	SaveableActorData.Add(ActorID, ActorData);
}

FSaveActorData UTFGameInstance::GetActorData(const FGuid& ActorID)
{
	return SaveableActorData[ActorID];
}

void UTFGameInstance::DEVSaveGame()
{
	if (SaveGameObject == nullptr)
	{
		CreateSaveSlot();
	}
	GatherActorDAta();
	SaveGameObject->SetSaveActorData(SaveableActorData);
	SaveGameObject->SetPlayerData(PlayerData);
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameName, 0);
}

void UTFGameInstance::DEVLoadGame()
{
	LoadGame(); 
}
