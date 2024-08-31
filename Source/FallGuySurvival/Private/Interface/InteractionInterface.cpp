// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/InteractionInterface.h"

// Add default functionality here for any IInteractionInterface functions that are not pure virtual.

void IInteractionInterface::Interact_Implementation(ATFCharacter* Caller)
{
}

bool IInteractionInterface::IsInteractable_Implementation() const
{
	return false;
}
