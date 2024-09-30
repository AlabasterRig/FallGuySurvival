// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDayLength.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EDayLength : uint8
{
	DEFAULT = 0,
	MIN30 = 1 UMETA(DisplayName = "30 Mins"),
	MIN60 = 2 UMETA(DisplayName = "60 Mins"),
	MIN120 = 4 UMETA(DisplayName = "120 Mins"),
	MIN180 = 6 UMETA(DisplayName = "180 Mins"),
	MIN240 = 8 UMETA(DisplayName = "240 Mins"),
	MIN300 = 10 UMETA(DisplayName = "300 Mins")
};