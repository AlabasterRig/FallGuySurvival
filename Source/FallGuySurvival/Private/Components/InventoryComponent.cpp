// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UInventoryComponent::IsOverCarryWeight(TSubclassOf<class UItemBase> Item)
{
	return false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItemToTop(TSubclassOf<UItemBase> Item)
{
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (CurrentWeight + ItemWeight > MaxWeight)
	{
		return false;
	}
	InventoryContents.Insert(Item, 0);
	CurrentWeight += ItemWeight;
	return true;
}

bool UInventoryComponent::AddItemAtIndex(TSubclassOf<class UItemBase> Item, const int& Index)
{
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (CurrentWeight + ItemWeight > MaxWeight)
	{
		return false;
	}
	return true;
}

bool UInventoryComponent::AddItemToStackAtIndex(TSubclassOf<class UItemBase> Item, const int& Index)
{
	return false;
}

