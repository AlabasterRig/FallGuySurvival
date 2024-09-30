// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECoreStat.generated.h"

UENUM(BlueprintType)
enum class ECoreStat : uint8
{
	CS_HEALTH UMETA(DisplayName = "Health"),
	CS_STAMINA UMETA(DisplayName = "Stamina"),
	CS_HUNGER UMETA(DisplayName = "Hunger"),
	CS_THIRST UMETA(DisplayName = "Thirst")
};