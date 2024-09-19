// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

int UItemBase::AddToStack(const int& Amount)
{
    int Remains = 0;
    if (CurrentStackSize == MaxStackSize)
    {
        return Amount;
    }
	Remains = FMath::Clamp(Amount - (MaxStackSize - CurrentStackSize), 0, Amount);
	CurrentStackSize += (Amount - Remains);
    return Remains;
}

int UItemBase::RemoveFromStack(const int& Amount)
{
    if (CurrentStackSize < Amount)
    {
        int Removed = CurrentStackSize;
        CurrentStackSize = 0;
		return Removed;
    }
	CurrentStackSize -= Amount;
    return 0;
}
