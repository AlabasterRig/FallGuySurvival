// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFActor.h"
#include "Data/EDayLength.h"
#include "Data/FTimeData.h"
#include "TFChronomanagerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeChangeDelegate, FTimeData, TimeData);

UCLASS()
class FALLGUYSURVIVAL_API ATFChronomanagerBase : public ATFActor
{
	GENERATED_BODY()
	
private:

#pragma region TimeOfDay

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Use Day/Night Cycle"), Category = " Chrono|Time")
	bool bUseDayNightCycle = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Current Time of Day information"), Category = " Chrono|Time")
	FTimeData CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Time")
	float DayLengthInMinutes = 10;

#pragma endregion

#pragma region Lighting

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = "Chrono|Lighting")
	class ADirectionalLight* SunLight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = "Chrono|Time")
	class UCurveLinearColor* DailySunRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = "Chrono|Time")
	class UCurveLinearColor* AnnualSunRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = "Chrono|Time")
	class UCurveLinearColor* SkyLightDailyColour;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = "Chrono|Time")
	class ASkyLight* SkyLight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = "Chrono|Time")
	float MaxSunIntensity = 10.0;

#pragma endregion

#pragma region Temperature

	FTimerHandle WorldTemperatureHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Number of Seconds between Temperature Updates"), Category = "Chrono|Temperature")
	float WorldTemperatureTickRate = 5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Current Ambient/World Temperature in °C"), Category = "Chrono|Temperature")
	float CurrentWorldTemperature = 27;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Daily Temperature Range"), Category = "Chrono|Temperature")
	class UCurveFloat* DailyTemperatureRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Tooltip = "Annual Temperature Range"), Category = "Chrono|Temperature")
	class UCurveFloat* AnnualTemperatureRange;

#pragma endregion

	bool bTimeWasUpdated = false;
	float TimeDecay = 0;
	float MinuteLength = 0;
	float CurrentTimeOfDay = 0;

	void UpdateTime(const float& DeltaTime);
	void AdvanceMinute();
	void AdvanceHour();
	void AdvanceDay();
	void AdvanceMonth();
	void AdvanceYear();
	void SetDayOfYear();
	void CalculateDayLength();
	void UpdateTimeOfDayRef();
	void UpdateLighting();
	void UpdateLightRotation();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateFromSave_Implementation() override;

	UPROPERTY(BlueprintAssignable)
	FTimeChangeDelegate OnTimeChange;
	FTimeData GetCurrentGameTime() const { return CurrentTime; }

	FSaveActorData GetSaveData_Implementation() override;
	void SetActorRawSaveData_Implementation(const TArray<FString>& Data) override;

	UFUNCTION()
	void UpdateTemperature();
};
