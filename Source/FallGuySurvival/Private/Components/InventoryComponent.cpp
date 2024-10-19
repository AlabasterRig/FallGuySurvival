// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Items/ItemBase.h"
#include "Logger.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UInventoryComponent::IsOverCarryWeight(const float& ItemWeight) const
{
	if (CurrentWeight + ItemWeight > MaxWeight)
	{
		return true;
	}
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
	if (!IsValid(Item))
	{
		Logger::GetInstance()->AddMessage("UInventoryComponent::AddItemToTop - Invalid Item", EL_ERROR);
		return false;
	}
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (IsOverCarryWeight(ItemWeight))
	{
		return false;
	}
	InventoryContents.Insert(Item, 0);
	CurrentWeight += ItemWeight;
	return true;
}

bool UInventoryComponent::AddItemAtIndex(TSubclassOf<UItemBase> Item, int& Index)
{
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (IsOverCarryWeight(ItemWeight))
	{
		return false;
	}
	if (Index > InventoryContents.Num())
	{
		Index = InventoryContents.Num();
	}
	InventoryContents.Insert(Item, Index); // TODO: Debug to find potential error (Future)
	CurrentWeight += ItemWeight;
	return false;
}

bool UInventoryComponent::AddItemToStackAtIndex(TSubclassOf<UItemBase> Item, const int& Index)
{
	float ItemWeight = Item.GetDefaultObject()->GetStackWeight();
	if (IsOverCarryWeight(ItemWeight))
	{
		return false;
	}
	if (Index > InventoryContents.Num())
	{
		Logger::GetInstance()->AddMessage("UInventoryComponent::AddItemToStackAtIndex - Invalid Index", EL_ERROR);
		return false;
	}
	UItemBase* TargetItem = Cast<UItemBase>(InventoryContents[Index]);
	int Remain = TargetItem->AddToStack(Item.GetDefaultObject()->GetCurrentStack());
	if (Remain > 0)
	{
		Item.GetDefaultObject()->SetStackSize(Remain);
		InventoryContents.Insert(Item, 0);
	}
	CurrentWeight += ItemWeight;
	return true;
}

TArray<FItemUIData> UInventoryComponent::GetInventoryUIData() const
{
	TArray<FItemUIData> Ret;
	for (int Index = 0; Index < InventoryContents.Num(); Index++)
	{
		Ret.Add(InventoryContents[Index].GetDefaultObject()->GetUIData(Index));
	}
	return Ret;
}

