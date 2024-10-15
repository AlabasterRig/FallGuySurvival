// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFHarvestActorBase.h"
#include "Data/FTimeData.h"
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

	class ATFChronomanagerBase* TimeManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int NumberOfDaysToRegrow = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	int DaysSinceLastHarvest = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int ItemRegrowthAmount = 1; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	FTimeData TrackHarvest;

	void ResetHarvest();

protected:
	virtual void BeginPlay();

public:
	void OnDayChange();

	UFUNCTION()
	void OnTimeChange(FTimeData TimeData);
	void Interact_Implementation(class ATFCharacter* Caller) override;
	virtual FSaveActorData GetSaveData_Implementation() override;
	virtual void UpdateFromSave_Implementation() override;

};
