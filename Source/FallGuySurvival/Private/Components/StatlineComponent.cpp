// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatlineComponent.h"
#include "TF_Utils.h"
#include "GameFramework/CharacterMovementComponent.h"


void UStatlineComponent::TickStats(const float& DeltaTime)
{
	TickStamina(DeltaTime);
	TickHunger(DeltaTime);
	TickThirst(DeltaTime);
	if (Thirst.GetCurrent() <= 0.0 || Hunger.GetCurrent() <= 0.0)
	{
		return;
	}
	Health.TickStat(DeltaTime);
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

	if (!bIsSprinting && !OwningCharacterMovementComp->IsFalling()) // Stamina Regen
	{
		Stamina.TickStat(0 + (DeltaTime * SprintRegenerationPerSecond));
	}
}

void UStatlineComponent::TickHunger(const float& DeltaTime)
{
	if (Hunger.GetCurrent() <= 0.0)
	{
		Health.Adjust(0 - abs(StarvingHealthDamagePerSecond * DeltaTime));
		return;
	}

	Hunger.TickStat(DeltaTime);
}

void UStatlineComponent::TickThirst(const float& DeltaTime)
{
	if (Thirst.GetCurrent() <= 0.0)
	{
		Health.Adjust(0 - abs(DehydrationHealthDamagePerSecond * DeltaTime));
		return;
	}

	Thirst.TickStat(DeltaTime);
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
		Logger::GetInstance()->AddMessage("UStatlineComponent::GetStatPercentile called with invalid stat type", ErrorLevel::EL_WARNING);
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
	if (bIsSneaking && !bIsSprinting)
	{
		return; 
	}
	bIsSneaking = false;
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

void UStatlineComponent::SetSneaking(const bool& IsSneaking)
{
	bIsSneaking = IsSneaking;
	if (bIsSprinting && !bIsSneaking)
	{
		return;
	}
	bIsSprinting = false;
	OwningCharacterMovementComp->MaxWalkSpeed = bIsSneaking ? SneakSpeed : WalkSpeed;
}

void UStatlineComponent::SetMovementCompReference(UCharacterMovementComponent* Comp)
{
	OwningCharacterMovementComp = Comp;
}

FSaveComponentsData UStatlineComponent::GetComponentSaveData_Implementation()
{
	FSaveComponentsData Ret;
	Ret.ComponentClass = this->GetClass();
	Ret.RawData.Add(Health.GetSaveString());
	Ret.RawData.Add(Stamina.GetSaveString());
	Ret.RawData.Add(Hunger.GetSaveString());
	Ret.RawData.Add(Thirst.GetSaveString());
	// Add Additional Data added here needs to be included in the SetComponentsSaveData_Implementation().

	return Ret;
}

void UStatlineComponent::SetComponentSaveData_Implementation(FSaveComponentsData Data)
{
	TArray<FString> Parts;
	for (int i = 0; i < Data.RawData.Num(); i++)
	{
		Parts.Empty();
		Parts = StringChop(Data.RawData[i], '|');
		switch (i)
		{
		case 0:
			Health.UpdateFromSaveString(Parts);
			break;
		case 1:
			Stamina.UpdateFromSaveString(Parts);
			break;
		case 2:
			Hunger.UpdateFromSaveString(Parts);
			break;
		case 3:
			Thirst.UpdateFromSaveString(Parts);
			break;
		default:
			Logger::GetInstance()->AddMessage("UStatlineComponent::SetComponentSaveData_Implementation called with invalid stat data", ErrorLevel::EL_WARNING);
			break;
		}
	}
}

void UStatlineComponent::AdjustStat(const ECoreStat& Stat, const float& Amount)
{
	switch (Stat)
	{
	case ECoreStat::CS_HEALTH:
		Health.Adjust(Amount);
	case ECoreStat::CS_STAMINA:
		Stamina.Adjust(Amount);
	case ECoreStat::CS_HUNGER:
		Hunger.Adjust(Amount);
	case ECoreStat::CS_THIRST:
		Thirst.Adjust(Amount);
	default:
		Logger::GetInstance()->AddMessage("UStatlineComponent::AdjustStat called with invalid stat type", ErrorLevel::EL_WARNING);
		break;
	}
	return;
}

