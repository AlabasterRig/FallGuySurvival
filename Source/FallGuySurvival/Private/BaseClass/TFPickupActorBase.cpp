// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFPickupActorBase.h"
#include "Components/InventoryComponent.h"
#include "BaseClass/TFCharacter.h"
#include "Items/ItemBase.h"
#include "Logger.h"

ATFPickupActorBase::ATFPickupActorBase()
{
	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("World Mesh"));
	WorldMesh->SetupAttachment(RootComponent);
	WorldMesh->SetSimulatePhysics(true);
}

void ATFPickupActorBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(PhysicsTimer, this, &ATFPickupActorBase::StopPhysics, 2.0f, false);
}

FText ATFPickupActorBase::GetInteractionText_Implementation()
{
	return InteractionText;
}

void ATFPickupActorBase::Interact_Implementation(ATFCharacter* Caller)
{
	if (!IsValid(InventoryItem))
	{
		Logger::GetInstance()->AddMessage("ATFPickupActorBase::Interact_Implementation - Invalid Inventory Item", ErrorLevel::EL_ERROR);
		return;
	}

	UInventoryComponent* Inventory = Caller->GetInventory();
	int Remain = ItemCount;
	while (Remain > 0 && Inventory->AddItemToTop(InventoryItem))
	{
		Remain--;
	}
	if (Remain == 0)
	{
		this->Destroy();
		return;
	}
	ItemCount = Remain;
	return;
}

bool ATFPickupActorBase::IsInteractable_Implementation() const
{
	return true;
}

void ATFPickupActorBase::SetWorldMesh(UStaticMesh* Mesh)
{
	WorldMesh->SetStaticMesh(Mesh);
}

void ATFPickupActorBase::SetInventoryItem(TSubclassOf<UItemBase> Item)
{
	InventoryItem = Item;
	InteractionText = InventoryItem.GetDefaultObject()->GetPickupText();
}

void ATFPickupActorBase::StopPhysics()
{
	WorldMesh->SetSimulatePhysics(false);
	GetWorld()->GetTimerManager().ClearTimer(PhysicsTimer);
}
