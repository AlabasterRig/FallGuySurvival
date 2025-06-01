// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFCharacter.h"
#include "Components/StatlineComponent.h"
#include "Components/InventoryComponent.h"

// Sets default values
ATFCharacter::ATFCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Statline = CreateDefaultSubobject<UStatlineComponent>(TEXT("Statline"));
	Statline->SetMovementCompReference(GetCharacterMovement()); // TODO: Refactor Statline to use GetOwner function instead
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	SaveActorID = FGuid::NewGuid();
}

// Called when the game starts or when spawned
void ATFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!SaveActorID.IsValid())
	{
		SaveActorID = FGuid::NewGuid();
	}
}

bool ATFCharacter::CanJump() const
{
	return Statline->CanJump();
}

void ATFCharacter::HasJumped()
{
	Statline->HasJumped();
	ACharacter::Jump();
}

bool ATFCharacter::CanSprint() const
{
	return Statline->CanSprint();
}

void ATFCharacter::SetSprinting(const bool& IsSprinting)
{
	Statline->SetSprinting(IsSprinting);
}

void ATFCharacter::SetSneaking(const bool& IsSneaking)
{
	Statline->SetSneaking(IsSneaking);
}

// Called every frame
void ATFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FGuid ATFCharacter::GetActorSaveID_Implementation()
{
	return SaveActorID;
}

FSaveActorData ATFCharacter::GetSaveData_Implementation()
{
	FSaveActorData Ret;
	Ret.ActorClass = this->GetClass();
	Ret.ActorTransform = this->GetTransform();
	Ret.WasSpawned = this->bWasSpawned;
	return Ret;
}

void ATFCharacter::SetActorGuid_Implementation(const FGuid& NewGuid)
{
	if (SaveActorID.IsValid())
	{
		SaveActorID.Invalidate();
	}
	SaveActorID = NewGuid;
}

void ATFCharacter::SetWasSpawned(const bool& IsSpawned)
{
	bWasSpawned = IsSpawned;
}

