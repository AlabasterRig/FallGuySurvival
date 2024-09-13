// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Components/StatlineComponent.h"
#include "ConsumableItemBase.generated.h"

UCLASS()
class FALLGUYSURVIVAL_API UConsumableItemBase : public UItemBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<ECoreStat, float> StatAdjustments;

public:
	void OnUse(class ATFCharacter* Caller) override;
};
