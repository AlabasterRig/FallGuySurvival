// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFRegrowingHarvestActorBase.h"
#include "BaseClass/TFChronomanagerBase.h"
#include "TF_Utils.h"
#include "Kismet/GameplayStatics.h"
#include "Logger.h"

ATFRegrowingHarvestActorBase::ATFRegrowingHarvestActorBase()
{

}

void ATFRegrowingHarvestActorBase::ResetHarvest()
{
	bIsHarvested = false;
	ItemCount = ItemRegrowthAmount;
	HarvestMesh->bHiddenInGame = false;
	MarkComponentsRenderStateDirty();
}

void ATFRegrowingHarvestActorBase::BeginPlay()
{
	Super::BeginPlay();
	TimeManager = Cast<ATFChronomanagerBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ATFChronomanagerBase::StaticClass()));
	if (!IsValid(TimeManager))
	{
		Logger::GetInstance()->AddMessage("ATFRegrowingHarvestActorBase::BeginPlay - No Valid TimeManager", ErrorLevel::EL_CRITICAL);
		return;
	}
	TimeManager->OnTimeChange.AddUniqueDynamic(this, &ATFRegrowingHarvestActorBase::OnTimeChange);

}

void ATFRegrowingHarvestActorBase::OnDayChange()
{
	DaysSinceLastHarvest++;
	if (DaysSinceLastHarvest < NumberOfDaysToRegrow)
	{
		return;
	}
	ResetHarvest();
}

void ATFRegrowingHarvestActorBase::OnTimeChange(FTimeData TimeData)
{
	if (!bIsHarvested)
	{
		return;
	}

	if (TimeData.Day == TrackHarvest.Day)
	{
		return;
	}
	OnDayChange();
	TrackHarvest = TimeData;
}

void ATFRegrowingHarvestActorBase::Interact_Implementation(ATFCharacter* Caller)
{
	ATFHarvestActorBase::Interact_Implementation(Caller);
	if (!IsValid(TimeManager))
	{
		Logger::GetInstance()->AddMessage("ATFRegrowingHarvestActorBase::Interact_Implementation - No Valid TimeManager", ErrorLevel::EL_CRITICAL);
		return;
	}
	if (!bIsHarvested)
	{
		return;
	}
	TrackHarvest = TimeManager->GetCurrentGameTime();
}

FSaveActorData ATFRegrowingHarvestActorBase::GetSaveData_Implementation()
{
	TArray<FString> RawData;
	RawData.Add(TrackHarvest.GetSaveString());
	return FSaveActorData(GetActorTransform(), bWasSpawned, ATFRegrowingHarvestActorBase::StaticClass(), RawData);
}

void ATFRegrowingHarvestActorBase::UpdateFromSave_Implementation()
{
	TrackHarvest.DayOfYear = TrackHarvest.Day;
	UpdateHarvestState();
}

void ATFRegrowingHarvestActorBase::SetActorRawSaveData_Implementation(const TArray<FString>& Data)
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
			TrackHarvest.UpdateFromSaveString(StringChunks);
			break;
		default:
			Logger::GetInstance()->AddMessage("ATFRegrowingHarvestActorBase::SetActorRawSaveData_Implementation - Out of bounds index operator", ErrorLevel::EL_ERROR);
			break;
		}
		i++; // Currently one case but i++ for future proofing
	}
}

