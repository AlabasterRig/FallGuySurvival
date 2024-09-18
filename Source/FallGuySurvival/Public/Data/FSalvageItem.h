// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSalvageItem.generated.h"

USTRUCT(BlueprintType)
struct FSalvageItem
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Quantity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Tag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UJunkItemBase> Item;
};