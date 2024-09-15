// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

void UItemBase::OnUse(ATFCharacter* Caller)
{
}

float UItemBase::GetStackWeight(const int Amount) const
{
    return ItemWeight * Amount;
}

float UItemBase::GetItemWeight() const
{
    return ItemWeight;
}

FItemUIData UItemBase::GetUIData() const
{
    return FItemUIData(ItemName, ItemDescription, ItemIcon);
}
