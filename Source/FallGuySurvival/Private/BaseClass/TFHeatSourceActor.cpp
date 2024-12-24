// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFHeatSourceActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATFHeatSourceActor::ATFHeatSourceActor()
{
	HeatZone = CreateDefaultSubobject<USphereComponent>(TEXT("Heat Zone"));
	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("World Mesh"));
	ParticleEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Emitter"));

	WorldMesh->SetupAttachment(RootComponent);
	HeatZone->SetupAttachment(WorldMesh);
	ParticleEmitter->SetupAttachment(WorldMesh);
	HeatZone->OnComponentBeginOverlap.AddDynamic(this, &ATFHeatSourceActor::OnHeatZoneOverlapBegin);
	HeatZone->OnComponentEndOverlap.AddDynamic(this, &ATFHeatSourceActor::OnHeatZoneOverlapEnd);
}

void ATFHeatSourceActor::BeginPlay()
{
	SphereRadius = HeatZone->GetScaledSphereRadius();
}

void ATFHeatSourceActor::OnHeatZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 
}

void ATFHeatSourceActor::OnHeatZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyindex)
{
}

FText ATFHeatSourceActor::GetInteractionText_Implementation()
{
	return bIsActivated ? DisableText : EnableText;
}

void ATFHeatSourceActor::Interact_Implementation(ATFCharacter* Caller)
{
	if (bIsActivated)
	{
		return;
	}
	return;
}

bool ATFHeatSourceActor::IsInteractable_Implementation() const
{
	return bInteractableHeatSource;
}
