// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFPickupActorBase.h"
#include "Components/InventoryComponent.h"
#include "BaseClass/TFCharacter.h"
#include "Items/ItemBase.h"

ATFPickupActorBase::ATFPickupActorBase()
{
	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("World Mesh"));
	WorldMesh->SetupAttachment(RootComponent);
}

FText ATFPickupActorBase::GetInteractionText_Implementation()
{
	return InteractionText;
}

void ATFPickupActorBase::Interact_Implementation(ATFCharacter* Caller)
{
	if (!IsValid(InventoryItem))
	{
		// TODO: Error Logging
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
		// this->SetAutoDestroyWhenFinished(true);
		return;
	}
	ItemCount = Remain;
	return;

	/* 
		UInventoryComponent* InvetComp = Caller->GetInventory();
		int rem = -1;
		if(rem = InvetComp->AddItem(InvetoryItem, ItemCount) == 0) 
		{
			this->Destroy();
			return;
		}
		ItemCount = rem;
		return;
	*/
}

bool ATFPickupActorBase::IsInteractable_Implementation() const
{
	return true;
}
