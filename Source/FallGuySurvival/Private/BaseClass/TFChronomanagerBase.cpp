// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFChronomanagerBase.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"

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
	SetDayOfYear();
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
		// TODO: Log Invalid Month
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
	switch (CurrentTime.Month)
	{
	case 12:
		CurrentTimeOfDay += 30;
	case 11:
		CurrentTimeOfDay += 31;
	case 10:
		CurrentTimeOfDay += 30;
	case 9:
		CurrentTimeOfDay += 31;
	case 8:
		CurrentTimeOfDay += 31;
	case 7:
		CurrentTimeOfDay += 30;
	case 6:
		CurrentTimeOfDay += 31;
	case 5:
		CurrentTimeOfDay += 30;
	case 4:
		CurrentTimeOfDay += 31;
	case 3:
		CurrentTimeOfDay += CurrentTime.Year % 4 == 0 ? 29 : 28;
	case 2:
		CurrentTimeOfDay += 31;
	case 1:
		CurrentTime.DayOfYear = CurrentTime.Day;
	default:
		// TODO: Log Invalid Month
		break;
	}
}

void ATFChronomanagerBase::CalculateDayLength()
{
	MinuteLength = (DayLengthInMinutes * 60) / 1440;
	TimeDecay = MinuteLength;
}

void ATFChronomanagerBase::UpdateTimeOfDayRef()
{
	CurrentTimeOfDay = (CurrentTime.Hour * 60) + CurrentTime.Minute;
}

void ATFChronomanagerBase::UpdateLighting()
{
	if (!IsValid(SunLight) || !IsValid(DailySunIntensity))
	{
		// TODO: Log Error for missing Light
		return;
	}
	float NewLightIntensity = DailySunIntensity->GetFloatValue(CurrentTimeOfDay);
	if (IsValid(AnnualSunIntensity))
	{
		NewLightIntensity += AnnualSunIntensity->GetFloatValue(CurrentTime.DayOfYear);
	}
	NewLightIntensity = FMath::Clamp(NewLightIntensity, 0, MaxSunIntensity);
	
	SunLight->GetLightComponent()->Intensity = NewLightIntensity;
	SunLight->GetLightComponent()->UpdateColorAndBrightness();  // Update Intensity, Colour and forces it to be re-rendered.
	// TODO: Add in SkyLight update.
}

void ATFChronomanagerBase::UpdateLightRotation()
{
	if (!IsValid(SunLight) || !IsValid(DailySunRotation))
	{
		// TODO: Log Error for missing light
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
}
