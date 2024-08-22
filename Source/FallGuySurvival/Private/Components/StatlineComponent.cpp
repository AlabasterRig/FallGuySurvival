// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatlineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UStatlineComponent::TickStats(const float& DeltaTime)
{
	Health.TickStat(DeltaTime);
	TickStamina(DeltaTime);
	Hunger.TickStat(DeltaTime);
	Thirst.TickStat(DeltaTime);
}

void UStatlineComponent::TickStamina(const float& DeltaTime)
{
	if (CurrentStaminaExhaustion > 0.0)
	{
		CurrentStaminaExhaustion -= DeltaTime;
		return;
	}

	if (bIsSprinting && IsValidSpriting())
	{
		Stamina.TickStat(0 - (DeltaTime * SprintCostMultiplier));
		if (Stamina.GetCurrent() <= 0)
		{
			SetSprinting(false);
			CurrentStaminaExhaustion = SecondsForStaminaExhaustion;
		}
		return;
	}

	Stamina.TickStat(DeltaTime);
}

bool UStatlineComponent::IsValidSpriting()
{
	return OwningCharacterMovementComp->Velocity.Length() > WalkSpeed && !OwningCharacterMovementComp->IsFalling();
}

// Sets default values for this component's properties
UStatlineComponent::UStatlineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatlineComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacterMovementComp->MaxWalkSpeed = WalkSpeed;
	
}


// Called every frame
void UStatlineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TickType != ELevelTick::LEVELTICK_PauseTick)
	{
		TickStats(DeltaTime);
	}
}

float UStatlineComponent::GetStatPercentile(const ECoreStat stat) const
{
	switch (stat)
	{
	case ECoreStat::CS_HEALTH:
		return Health.Percentile();
	case ECoreStat::CS_STAMINA:
		return Stamina.Percentile();
	case ECoreStat::CS_HUNGER:
		return Hunger.Percentile();
	case ECoreStat::CS_THIRST:
		return Thirst.Percentile();
	default:
		//Invalid Log Stat
		break;
	}
	return -1;
}

bool UStatlineComponent::CanSprint() const
{
	return Stamina.GetCurrent() > 0.0;
}

void UStatlineComponent::SetSprinting(const bool& IsSprinting)
{
	bIsSprinting = IsSprinting;
	OwningCharacterMovementComp->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}

bool UStatlineComponent::CanJump()
{
	return Stamina.GetCurrent() >= JumpCost;
}

void UStatlineComponent::HasJumped()
{
	Stamina.Adjust(JumpCost * -1);
}

void UStatlineComponent::SetMovementCompReference(UCharacterMovementComponent* Comp)
{
	OwningCharacterMovementComp = Comp;
}

