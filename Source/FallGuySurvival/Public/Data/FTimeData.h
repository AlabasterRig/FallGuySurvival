// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logger.h"
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

	FString GetSaveString()
	{
		FString Ret;
		Ret += FString::FromInt(DayOfYear);
		Ret += "|";
		Ret += FString::FromInt(Year);
		Ret += "|";
		Ret += FString::FromInt(Month);
		Ret += "|";
		Ret += FString::FromInt(Day);
		Ret += "|";
		Ret += FString::FromInt(Hour);
		Ret += "|";
		Ret += FString::FromInt(Minute);
		return Ret;
	}

	void UpdateFromSaveString(TArray<FString> Parts)
	{
		if (Parts.Num() != 6)
		{
			Logger::GetInstance()->AddMessage("FTimeData::UpdateFromSaveString called with other than 6 parts", ErrorLevel::EL_WARNING);
			return;
		}
		DayOfYear = FCString::Atoi(*Parts[0]);
		Year = FCString::Atoi(*Parts[1]);
		Month = FCString::Atoi(*Parts[2]);
		Day = FCString::Atoi(*Parts[3]);
		Hour = FCString::Atoi(*Parts[4]);
		Minute = FCString::Atoi(*Parts[5]);
	}
};