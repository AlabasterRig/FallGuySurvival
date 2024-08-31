// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFDoorBase.h"

ATFDoorBase::ATFDoorBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

FText ATFDoorBase::GetInteractionText_Implementation()
{
	return bIsOpen ? FText::FromString("Close") : FText::FromString("Open");
}

void ATFDoorBase::Interact_Implementation(ATFCharacter* Caller)
{
	Interact(Caller);
}

bool ATFDoorBase::IsInteractable_Implementation() const
{
	return true;
}
