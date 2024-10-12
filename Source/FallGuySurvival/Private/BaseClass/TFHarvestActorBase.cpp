// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFHarvestActorBase.h"
#include "Components/InventoryComponent.h"
#include "BaseClass/TFCharacter.h"
#include "Items/ItemBase.h"

ATFHarvestActorBase::ATFHarvestActorBase()
{
	PermanentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Permanent Mesh"));
	HarvestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Harvest Mesh"));
	PermanentMesh->SetupAttachment(RootComponent);
	HarvestMesh->SetupAttachment(PermanentMesh);
}

void ATFHarvestActorBase::UpdateHarvestState()
{
	HarvestMesh->bHiddenInGame = bIsHarvested;
	HarvestMesh->SetCollisionEnabled(bIsHarvested ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
	MarkComponentsRenderStateDirty();
}

FText ATFHarvestActorBase::GetInteractionText_Implementation()
{
	return InteractionText;
}

void ATFHarvestActorBase::Interact_Implementation(ATFCharacter* Caller)
{
	UInventoryComponent* Inventory = Caller->GetInventory();
	int Remain = ItemCount;
	while (Remain > 0 && Inventory->AddItemToTop(InventoryItem))
	{
		Remain--;
	}
	if (Remain == 0)
	{
		UpdateHarvestState();
		bIsHarvested = true;
		return;
	}
	ItemCount = Remain;
	return;
	
	/*
		UInventoryComponent* InvetComp = Caller->GetInventory();
		int rem = -1;
		if(rem = InvetComp->AddItem(InvetoryItem, ItemCount) == 0)
		{
	*/
	//UpdateHarvestState();
	//bIsHarvested = true;
	/*
			return;
		}
		ItemCount = rem;
		return;
	*/
}

bool ATFHarvestActorBase::IsInteractable_Implementation() const
{
	return !bIsHarvested;
}

FSaveActorData ATFHarvestActorBase::GetSaveData_Implementation()
{
	return FSaveActorData(GetActorTransform(), bWasSpawned, GetClass());
}

void ATFHarvestActorBase::UpdateFromSave_Implementation()
{
	UpdateHarvestState();
}
