// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFActor.h"
#include "Data/EDayLength.h"
#include "Data/FTimeData.h"
#include "TFChronomanagerBase.generated.h"

/**
 * 
 */
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Lighting")
	class ADirectionalLight* SunLight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Time")
	class UCurveFloat* DailySunIntensity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Time")
	class UCurveFloat* AnnualSunIntensity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Time")
	class UCurveLinearColor* DailySunRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Time")
	class UCurveLinearColor* AnnualSunRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Time")
	class ASkyLight* SkyLight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", Tooltip = "Day Length in Real World minutes"), Category = " Chrono|Time")
	class UCurveFloat* SkylightIntensity;

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

	void CalculateDayLength();
	void UpdateTimeOfDayRef();
	void UpdateLighting();
	void UpdateLightRotation(const float& DeltaTime);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
