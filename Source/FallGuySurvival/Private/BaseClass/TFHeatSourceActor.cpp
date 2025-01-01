// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFHeatSourceActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/StatlineComponent.h"
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
	if (!bIsActivated)
	{
		return;
	}
	// TODO: Add Consume Fuel Logic
	if (ActorsInRange.Num() == 0)
	{
		return;
	}
	for (const auto Actors : ActorsInRange)
	{
		if (!IsValid(Actors))
		{
			continue;
		}
		float ActorDistance = (Actors->GetActorLocation() - this->GetActorLocation()).Length();
		ActorDistance /= SphereRadius;
		float HeatMultiplier = HeatFalloff->GetFloatValue(ActorDistance);
		DEBUG_AppliedHeat = MaxHeatValue * HeatMultiplier;
		Actors->GetStatline()->AdjustLocalTempOffset(FMath::Clamp(MaxHeatValue * HeatMultiplier, 0, MaxHeatValue));
	}
}

void ATFHeatSourceActor::OnHeatZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//NOTE: Efficiency Issue with Cast.
	ATFCharacter* AsTFCharacter = Cast<ATFCharacter>(OtherActor);
	if (AsTFCharacter != nullptr)
	{
		ActorsInRange.AddUnique(AsTFCharacter);
	}
	if (!bIsActivated)
	{
		AsTFCharacter->GetStatline()->AdjustLocalTempOffset(0);
	}
}

void ATFHeatSourceActor::OnHeatZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyindex)
{
	//NOTE: Efficiency Issue with Cast.
	ATFCharacter* RemovedActors = Cast<ATFCharacter>(OtherActor);
	if (!IsValid(RemovedActors))
	{
		return;
	}
	if (ActorsInRange.Remove(RemovedActors) > 0)
	{
		RemovedActors->GetStatline()->AdjustLocalTempOffset(0);
	}
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
		OnInteractionBP_Implementation();
		return;
	}
	if (IsValid(ParticleEmitter))	
	{
		ParticleEmitter->Activate();
	}
	bIsActivated = true;
	OnInteractionBP_Implementation();
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

void ATFHeatSourceActor::OnInteractionBP_Implementation()
{
	OnInteractionBP();
}
