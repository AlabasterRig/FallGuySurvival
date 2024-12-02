// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFChronomanagerBase.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Logger.h"
#include "TF_Utils.h"

void ATFChronomanagerBase::UpdateTemperature()
{
	// Daily Temperature Range and Annual Temperature Range
	if (!IsValid(DailyTemperatureRange) || !IsValid(AnnualTemperatureRange))
	{
		GetWorld()->GetTimerManager().ClearTimer(WorldTemperatureHandle);
		Logger::GetInstance()->AddMessage("ATFChronomanagerBase::UpdateTemperature - DailyTemperatureRange or AnnualTemperatureRange is not valid", ErrorLevel::EL_WARNING);
		return;
	}

	float CurrentDailyTemperature = DailyTemperatureRange->GetFloatValue(CurrentTimeOfDay);
	float CurrentAnnualTemperature = AnnualTemperatureRange->GetFloatValue(CurrentTime.DayOfYear);
	CurrentWorldTemperature = CurrentDailyTemperature + CurrentAnnualTemperature;
	OnTemperatureChanged.Broadcast(CurrentWorldTemperature);
}

void ATFChronomanagerBase::UpdateTime(const float& DeltaTime)
{
	TimeDecay -= DeltaTime;
	if (TimeDecay <=0)
	{
		TimeDecay += MinuteLength;
		AdvanceMinute();
	}
}

void ATFChronomanagerBase::AdvanceMinute()
{
	bTimeWasUpdated = true;
	CurrentTime.Minute++;
	if (CurrentTime.Minute >= 60)
	{
		CurrentTime.Minute = 0;
		AdvanceHour();
	}
}

void ATFChronomanagerBase::AdvanceHour()
{
	bTimeWasUpdated = true;
	CurrentTime.Hour++;
	if (CurrentTime.Hour >= 24)
	{
		CurrentTime.Hour = 0;
		AdvanceDay();
	}
}

void ATFChronomanagerBase::AdvanceDay()  // Like a typical real world calendar, we have 30 days in a month or 31 days in a month
{
	bTimeWasUpdated = true;
	AddDayOfYear();
	CurrentTime.Day++;
	switch (CurrentTime.Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (CurrentTime.Day > 31)
		{
			CurrentTime.Day = 1;
			AdvanceMonth();
		}
		break;
	case 2:
		if (CurrentTime.Year % 4 == 0)
		{
			if (CurrentTime.Day > 29)
			{
				CurrentTime.Day = 1;
				AdvanceMonth();
			}
			break;
		}
		if (CurrentTime.Day > 28)
		{
			CurrentTime.Day = 1;
			AdvanceMonth();
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (CurrentTime.Day > 30)
		{
			CurrentTime.Day = 1;
			AdvanceMonth();
		}
		break;
	default:
		Logger::GetInstance()->AddMessage("ATFChronomanagerBase::AdvanceDay - Invalid Month, cannot advance day", EL_ERROR);
		break;
	}
}

void ATFChronomanagerBase::AdvanceMonth()
{
	bTimeWasUpdated = true;
	CurrentTime.Month++;
	if (CurrentTime.Month > 12)
	{
		CurrentTime.Month = 1;
		AdvanceYear();
	}
}

void ATFChronomanagerBase::AdvanceYear()
{
	bTimeWasUpdated = true;
	CurrentTime.Year++;
}

void ATFChronomanagerBase::SetDayOfYear()
{
	CurrentTime.DayOfYear = 0;
	switch (CurrentTime.Month)
	{
	case 12:
		CurrentTime.DayOfYear += 30;
	case 11:
		CurrentTime.DayOfYear += 31;
	case 10:
		CurrentTime.DayOfYear += 30;
	case 9:
		CurrentTime.DayOfYear += 31;
	case 8:
		CurrentTime.DayOfYear += 31;
	case 7:
		CurrentTime.DayOfYear += 30;
	case 6:
		CurrentTime.DayOfYear += 31;
	case 5:
		CurrentTime.DayOfYear += 30;
	case 4:
		CurrentTime.DayOfYear += 31;
	case 3:
		CurrentTime.DayOfYear += CurrentTime.Year % 4 == 0 ? 29 : 28;
	case 2:
		CurrentTime.DayOfYear += 31;
	case 1:
		CurrentTime.DayOfYear += CurrentTime.Day;
	}
}

void ATFChronomanagerBase::AddDayOfYear()
{
	CurrentTime.DayOfYear++;
	if (CurrentTime.Month == 1 && CurrentTime.Day == 1)
	{
		CurrentTime.DayOfYear = 1;
	}
}

void ATFChronomanagerBase::CalculateDayLength()
{
	MinuteLength = (DayLengthInMinutes * 60) / 1440;
	TimeDecay = MinuteLength;
	WorldTemperatureTickRate = MinuteLength * 15;
}

void ATFChronomanagerBase::UpdateTimeOfDayRef()
{
	CurrentTimeOfDay = (CurrentTime.Hour * 60) + CurrentTime.Minute;
}

void ATFChronomanagerBase::UpdateLighting()
{
	if (!IsValid(SunLight) || !IsValid(DailySunRotation))
	{
		Logger::GetInstance()->AddMessage("ATFChronomanagerBase::UpdateLighting - SunLight or DailySunIntensity is not valid", EL_ERROR);
		return;
	}
	float NewLightIntensity = DailySunRotation->GetUnadjustedLinearColorValue(CurrentTimeOfDay).A;
	if (IsValid(AnnualSunRotation))
	{
		NewLightIntensity += AnnualSunRotation->GetUnadjustedLinearColorValue(CurrentTimeOfDay).A;
	}
	NewLightIntensity = FMath::Clamp(NewLightIntensity, 0, MaxSunIntensity);
	
	SunLight->GetLightComponent()->Intensity = NewLightIntensity;
	SunLight->GetLightComponent()->UpdateColorAndBrightness();  // Update Intensity, Colour and forces it to be re-rendered.

	if (!IsValid(SkyLight) || !IsValid(SkyLightDailyColour))
	{
		Logger::GetInstance()->AddMessage("ATFChronomanagerBase::UpdateLighting - SkyLight or SkylightIntensity is not valid", EL_ERROR);
		return;
	}

	float NewSkyLightIntensity = SkyLightDailyColour->GetUnadjustedLinearColorValue(CurrentTimeOfDay).A;
	SkyLight->GetLightComponent()->SetIntensity(NewSkyLightIntensity);
	if (IsValid(SkyLightDailyColour))
	{
		FLinearColor NewSkyLightColour = SkyLightDailyColour->GetUnadjustedLinearColorValue(CurrentTimeOfDay);
		SkyLight->GetLightComponent()->SetLightColor(NewSkyLightColour);
	}
}

void ATFChronomanagerBase::UpdateLightRotation()
{
	if (!IsValid(SunLight) || !IsValid(DailySunRotation))
	{
		Logger::GetInstance()->AddMessage("ATFChronomanagerBase::UpdateLightRotation - SunLight or DailySunRotation is not valid", EL_ERROR);
		return;
	}
	FLinearColor ColourRotation = DailySunRotation->GetUnadjustedLinearColorValue(CurrentTimeOfDay);
	if (IsValid(AnnualSunRotation))
	{
		ColourRotation += AnnualSunRotation->GetUnadjustedLinearColorValue(CurrentTime.DayOfYear);
	}

	FRotator NewRotation(ColourRotation.G, ColourRotation.B, ColourRotation.R);
	SunLight->SetActorRotation(NewRotation);
}

void ATFChronomanagerBase::BeginPlay()
{
	Super::BeginPlay();
	CalculateDayLength();
	SetDayOfYear();
	GetWorld()->GetTimerManager().SetTimer(WorldTemperatureHandle, this, &ATFChronomanagerBase::UpdateTemperature, WorldTemperatureTickRate, true, 0);
}

void ATFChronomanagerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(WorldTemperatureHandle);
}

void ATFChronomanagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bUseDayNightCycle)
	{
		return;
	}
	UpdateTime(DeltaTime);
	UpdateTimeOfDayRef();
	UpdateLightRotation();
	UpdateLighting();
	if (bTimeWasUpdated)
	{
		OnTimeChange.Broadcast(CurrentTime);
	}
}

void ATFChronomanagerBase::UpdateFromSave_Implementation()
{
	CalculateDayLength();
	UpdateTimeOfDayRef();
	UpdateLightRotation();
	UpdateLighting();
}

FSaveActorData ATFChronomanagerBase::GetSaveData_Implementation()
{
	TArray<FString> RawData;
	RawData.Add(CurrentTime.GetSaveString());
	return FSaveActorData(GetActorTransform(), bWasSpawned, GetClass()->StaticClass(), RawData);
}

void ATFChronomanagerBase::SetActorRawSaveData_Implementation(const TArray<FString>& Data)
{
	int i = 0;
	TArray<FString> StringChunks;
	for (auto d : Data)
	{
		StringChunks.Empty();
		switch (i)
		{
		case 0:
			StringChunks = StringChop(d, '|');
			CurrentTime.UpdateFromSaveString(StringChunks);
			break;
		default:
			Logger::GetInstance()->AddMessage("ATFChronomanagerBase::SetActorRawSaveData_Implementation - Out of bounds index operator", ErrorLevel::EL_ERROR);
			break;
		}
		i++;
	}
}
