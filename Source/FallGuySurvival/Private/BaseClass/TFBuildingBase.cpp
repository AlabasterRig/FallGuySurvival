// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFBuildingBase.h"
#include "BaseClass/TFCharacter.h"
#include "Components/StatlineComponent.h"
#include "BaseClass/TFBuildingOpening.h"

ATFBuildingBase::ATFBuildingBase()
{
	PrimaryActorTick.bCanEverTick = false;

	BuildingInteriorVolume = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Interior Volume"));
	BuildingInteriorVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BuildingInteriorVolume->OnComponentBeginOverlap.AddDynamic(this, &ATFBuildingBase::OnInteriorZoneOverlapBegin);
	BuildingInteriorVolume->OnComponentEndOverlap.AddDynamic(this, &ATFBuildingBase::OnInteriorZoneOverlapEnd);
	BuildingInteriorVolume->bHiddenInGame = true;
}

void ATFBuildingBase::RecalculateSeal()
{
	CurrentSealState = 0;
	for (const auto Portal : ExteriorOpenings)
	{
		if (Portal->GetIsClosed())
		{
			CurrentSealState += SealValuePerPortal;
		}
	}
	CurrentSealState = FMath::Clamp(CurrentSealState, 0.0f, 1.0f);
	for (const auto Char : ActorsInside)
	{
		Char->GetStatline()->SetBuildingInsulation(BuildingInsulationValue * CurrentSealState);
	}
}

void ATFBuildingBase::OnInteriorZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATFCharacter* AsTFCharacter = Cast<ATFCharacter>(OtherActor);
	if (AsTFCharacter != nullptr)
	{
		ActorsInside.AddUnique(AsTFCharacter);
		AsTFCharacter->GetStatline()->SetBuildingInsulation(BuildingInsulationValue * CurrentSealState);
	}
}

void ATFBuildingBase::OnInteriorZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyindex)
{
	ATFCharacter* AsTFCharacter = Cast<ATFCharacter>(OtherActor);
	if (AsTFCharacter != nullptr)
	{
		ActorsInside.Remove(AsTFCharacter);
		AsTFCharacter->GetStatline()->SetBuildingInsulation(0);
	}
}

void ATFBuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATFBuildingBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ExteriorOpenings.Empty();
	for (auto c : RootComponent->GetAttachChildren())
	{
		ATFBuildingOpening* Child = Cast<ATFBuildingOpening>(c);
		if (IsValid(Child))
		{
			ExteriorOpenings.Add(Child);
			Child->SetParent(this);
		}
	}

	SealValuePerPortal = 1.0f / ExteriorOpenings.Num();
}