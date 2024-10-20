// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ERandomizedVector.h"

TArray<FString> StringChop(FString Source, char split = '|');

int RandomIntFromVector(const ERandomizedVector& DirectionRandomization, const FVector& Location);