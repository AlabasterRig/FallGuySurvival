// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFRegrowingHarvestActorBase.h"
#include "BaseClass/TFChronomanagerBase.h"
#include "Kismet/GameplayStatics.h"

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
		// TODO: Log Error
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
		// TODO: Log Error for no time manager
		return;
	}
	if (!bIsHarvested)
	{
		return;
	}
	TrackHarvest = TimeManager->GetCurrentTime();
}

