// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interface/SaveActorInterface.h"
#include "TFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API UTFGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	TMap<FGuid, FSaveActorData> SaveableActorData;
	UPROPERTY()
	class UTFSaveGame* SaveGameObject = nullptr;
	FString SaveGameName = TEXT("DEFAULT");
	FName CurrentlyLoadedLevel = "NONE";

	UTFGameInstance();

	void CreateSaveSlot();
	void GatherActorDAta();
	void LoadGame();

public:
	UFUNCTION(BlueprintCallable)
	void AddActorData(const FGuid& ActorID, FSaveActorData ActorData);
	UFUNCTION(BlueprintCallable)
	FSaveActorData GetActorData(const FGuid& ActorID);

	UFUNCTION(BlueprintCallable)
	void DEVSaveGame();
	UFUNCTION(BlueprintCallable)
	void DEVLoadGame();
};
