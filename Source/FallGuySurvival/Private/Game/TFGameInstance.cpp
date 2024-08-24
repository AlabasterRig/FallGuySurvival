// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TFGameInstance.h"
#include "Game/TFSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

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

		SaveableActorData.Add(SaveAI, SaveAD);

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
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameName, 0);
}
