// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/FSaveComponentsData.h"
#include "CoreMinimal.h"

USTRUCT(BlueprintType)
struct FSaveActorData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform ActorTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FSaveComponentsData> ComponentData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool WasSpawned = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UClass* ActorClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> RawData;

	FSaveActorData()
	{

	};

	FSaveActorData(const FTransform actorTrans, const bool& wasSpawned, UClass* actorClass)
	{
		ActorTransform = actorTrans;
		WasSpawned = wasSpawned;
		ActorClass = actorClass;
	}

	FSaveActorData(const FTransform actorTrans, const bool& wasSpawned, UClass* actorClass, TArray<FString> Raw)
	{
		ActorTransform = actorTrans;
		WasSpawned = wasSpawned;
		ActorClass = actorClass;
		RawData = Raw;
	}
};