// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFHeatSourceActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseClass/TFCharacter.h"
#include "NiagaraComponent.h"

ATFHeatSourceActor::ATFHeatSourceActor()
{
	HeatZone = CreateDefaultSubobject<USphereComponent>(TEXT("Heat Zone"));
	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("World Mesh"));
	ParticleEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle Emitter"));

	WorldMesh->SetupAttachment(RootComponent);
	HeatZone->SetupAttachment(WorldMesh);
	ParticleEmitter->SetupAttachment(WorldMesh);
	HeatZone->OnComponentBeginOverlap.AddDynamic(this, &ATFHeatSourceActor::OnHeatZoneOverlapBegin);
	HeatZone->OnComponentEndOverlap.AddDynamic(this, &ATFHeatSourceActor::OnHeatZoneOverlapEnd);

	PrimaryActorTick.TickInterval = 1;
}

void ATFHeatSourceActor::BeginPlay()
{
	Super::BeginPlay();
	SphereRadius = HeatZone->GetScaledSphereRadius();
	if (!IsValid(HeatFalloff))
	{
		PrimaryActorTick.SetTickFunctionEnable(false);
	}
	if (IsValid(ParticleEmitter) && bIsActivated)
	{
		ParticleEmitter->Activate();
	}
}

void ATFHeatSourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActivated || !IsValid(HeatFalloff))
	{
		return;
	}
	// TODO: Add Consume Fuel Logic
	if (ActorsInRange.Num() == 0)
	{
		return;
	}
	for (const auto a : ActorsInRange)
	{
		if (!IsValid(a))
		{
			continue;
		}
		float ActorDistance = (a->GetActorLocation() - this->GetActorLocation()).Length();
		ActorDistance /= SphereRadius;
		float HeatMultiplier = HeatFalloff->GetFloatValue(ActorDistance);
		float AppliedHeat = MaxHeatValue * HeatMultiplier;
		
		DEBUG_AppliedHeat = AppliedHeat;
	}
}

void ATFHeatSourceActor::OnHeatZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ATFCharacter>(OtherActor) != nullptr)
	{
		ActorsInRange.AddUnique(OtherActor);
	}
}

void ATFHeatSourceActor::OnHeatZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyindex)
{
	ActorsInRange.Remove(OtherActor);
}

FText ATFHeatSourceActor::GetInteractionText_Implementation()
{
	return bIsActivated ? DisableText : EnableText;
}

void ATFHeatSourceActor::Interact_Implementation(ATFCharacter* Caller)
{
	if (bIsActivated)
	{
		if (IsValid(ParticleEmitter))
		{
			ParticleEmitter->Deactivate();
		}
		bIsActivated = false;
		return;
	}
	if (IsValid(ParticleEmitter))	
	{
		ParticleEmitter->Activate();
	}
	bIsActivated = true;
	return;
}

bool ATFHeatSourceActor::IsInteractable_Implementation() const
{
	return bInteractableHeatSource;
}

void ATFHeatSourceActor::UpdateFromSave_Implementation()
{
	if (IsValid(ParticleEmitter) && bIsActivated)
	{
		ParticleEmitter->Activate();
	}
}
