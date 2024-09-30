// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTimeData.generated.h"

USTRUCT(BlueprintType)
struct FTimeData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Time")
	int DayOfYear = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Time")
	int Year = 2024;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Time")
	int Month = 9;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Time")
	int Day = 30;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Time")
	int Hour = 12;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Time")
	int Minute = 0;
};