// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFHarvestActorBase.h"
#include "TFRegrowingHarvestActorBase.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API ATFRegrowingHarvestActorBase : public ATFHarvestActorBase
{
	GENERATED_BODY()
	
private:
	ATFRegrowingHarvestActorBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int NumberOfDaysToRegrow = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int DaysSinceLastHarvest = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int ItemRegrowthAmount = 1; 

	void ResetHarvest();

protected:
	virtual void BeginPlay();

public:
	void OnDayChange();
};
