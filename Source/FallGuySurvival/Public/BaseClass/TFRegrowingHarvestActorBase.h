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

	class ATFChronomanagerBase* TimeManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvest", meta = (AllowPrivateAccess = "true"))
	int NumberOfDaysToRegrow = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Harvest", SaveGame, meta = (AllowPrivateAccess = "true"))
	int DaysSinceLastHarvest = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Harvest", meta = (AllowPrivateAccess = "true"))
	int ItemRegrowthAmount = 1; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Harvest", SaveGame, meta = (AllowPrivateAccess = "true"))
	FTimeData TrackHarvest;

	void ResetHarvest();

protected:
	virtual void BeginPlay();

public:
	void OnDayChange();
	ATFRegrowingHarvestActorBase();
	UFUNCTION()
	void OnTimeChange(FTimeData TimeData);
	void Interact_Implementation(class ATFCharacter* Caller) override;
	virtual FSaveActorData GetSaveData_Implementation() override;
	virtual void UpdateFromSave_Implementation() override;
	void SetActorRawSaveData_Implementation(const TArray<FString>& Data) override;
};
