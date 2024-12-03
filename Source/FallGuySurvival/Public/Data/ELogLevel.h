// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELogLevel : uint8
{
	LL_DEBUG = 0 UMETA(DisplayName = "Debug"),
	LL_WARNING = 1 UMETA(DisplayName = "Warning"),
	LL_ERROR = 2 UMETA(DisplayName = "Error"),
	LL_CRITICAL = 3 UMETA(DisplayName = "Critical")
};