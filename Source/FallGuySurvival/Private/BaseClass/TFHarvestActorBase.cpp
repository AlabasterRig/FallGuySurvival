// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFHarvestActorBase.h"

FText ATFHarvestActorBase::GetInteractionText_Implementation()
{
	return InteractionText;
}

void ATFHarvestActorBase::Interact_Implementation(ATFCharacter* Caller)
{
	/*
		UInventoryComponent* InvetComp = Caller->GetInventory();
		int rem = -1;
		if(rem = InvetComp->AddItem(InvetoryItem, ItemCount) == 0)
		{
	*/
	HarvestMesh->bHiddenInGame = true;
	bIsHarvested = true;
	/*
			return;
		}
		ItemCount = rem;
		return;
	*/
}

bool ATFHarvestActorBase::IsInteractable_Implementation() const
{
	return bIsHarvested ? false : true;
}
