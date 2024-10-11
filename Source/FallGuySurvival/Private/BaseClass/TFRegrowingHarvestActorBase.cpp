// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFRegrowingHarvestActorBase.h"
#include "BaseClass/TFChronomanagerBase.h"
#include "Data/FTimeData.h"
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
	ATFChronomanagerBase* TimeManager = Cast<ATFChronomanagerBase>(UGameplayStatics::GetActorOfClass(GetWorld(), ATFChronomanagerBase::StaticClass()));
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

}
