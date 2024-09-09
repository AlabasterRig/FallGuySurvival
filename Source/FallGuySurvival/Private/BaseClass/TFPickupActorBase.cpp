// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFPickupActorBase.h"

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
