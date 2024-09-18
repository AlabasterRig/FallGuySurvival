// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logger.h"
#include "CoreMinimal.h"
#include "FCoreStat.generated.h"

USTRUCT(BlueprintType)
struct FCoreStat
{
	GENERATED_USTRUCT_BODY();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	float Current = 100;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	float Max = 100;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	float PerSecondTick = 1;

public:
	FCoreStat()
	{

	}

	FCoreStat(const float& current, const float& max, const float& tick)
	{
		Current = current;
		Max = max;
		PerSecondTick = tick;
	}

	void TickStat(const float& DeltaTime)
	{
		Current = FMath::Clamp(Current + (PerSecondTick * DeltaTime), 0, Max);
	}

	void Adjust(const float& Amount)
	{
		Current = FMath::Clamp(Current + Amount, 0, Max);
	}

	float Percentile() const
	{
		return Current / Max;
	}

	float GetCurrent() const
	{
		return Current;
	}

	FString GetSaveString()
	{
		FString Ret = FString::SanitizeFloat(Current);
		Ret += "|";
		Ret += FString::SanitizeFloat(Max);
		Ret += "|";
		Ret += FString::SanitizeFloat(PerSecondTick);
		return Ret;
	}

	void UpdateFromSaveString(TArray<FString> Parts)
	{
		if (Parts.Num() != 3)
		{
			Logger::GetInstance()->AddMessage("FCoreStat::UpdateFromSaveString called with other than 3 parts", ErrorLevel::EL_WARNING);
			return;
		}
		Current = FCString::Atof(*Parts[0]);
		Max = FCString::Atof(*Parts[1]);
		PerSecondTick = FCString::Atof(*Parts[2]);
	}
};