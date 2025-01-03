// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Interface/SaveActorInterface.h"
#include "Data/FSaveActorData.h"
#include "TFSaveGame.generated.h"

UCLASS()
class FALLGUYSURVIVAL_API UTFSaveGame : public USaveGame
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TMap<FGuid, FSaveActorData> SaveableActorData;
	UPROPERTY()
	FName CurrentlyLoadedLevel = "NONE";
	UPROPERTY()
	struct FSaveActorData PlayerData;

public:
	void SetSaveActorData(TMap<FGuid, FSaveActorData> Data);
	TMap<FGuid, FSaveActorData> GetSaveActorData();
	void SetCurrentLevel(const FName Level);
	FName GetCurrentLevel();
	void SetPlayerData(FSaveActorData Data);
	FSaveActorData GetPlayerData();
};
