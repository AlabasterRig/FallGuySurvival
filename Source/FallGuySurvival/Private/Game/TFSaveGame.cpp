// Fill out your copyright notice in the Description page of Project Settings.

#include "Interface/SaveActorInterface.h"
#include "Game/TFSaveGame.h"

void UTFSaveGame::SetSaveActorData(TMap<FGuid, struct FSaveActorData> Data)
{
	SaveableActorData = Data;
}

TMap<FGuid, FSaveActorData> UTFSaveGame::GetSaveActorData()
{
	return SaveableActorData;
}

FName UTFSaveGame::GetCurrentLevel()
{
	return CurrentlyLoadedLevel;
}

void UTFSaveGame::SetCurrentLevel(const FName Level)
{
	CurrentlyLoadedLevel = Level;
}
