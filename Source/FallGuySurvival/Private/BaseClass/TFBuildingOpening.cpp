// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFBuildingOpening.h"
#include "BaseClass/TFBuildingBase.h"

void ATFBuildingOpening::SetParent(ATFBuildingBase* Parent)
{
	ParentBuilding = Parent;
}

bool ATFBuildingOpening::GetIsClosed() const
{
	return !bIsOpen;
}

FText ATFBuildingOpening::GetInteractionText_Implementation()
{
	return bIsOpen ? FText::FromString("Close") : FText::FromString("Open");
}

void ATFBuildingOpening::Interact_Implementation(ATFCharacter* Caller)
{
	Execute_Interact(this, Caller);
	ParentBuilding->RecalculateSeal();
}

bool ATFBuildingOpening::IsInteractable_Implementation() const
{
	return false;
}
