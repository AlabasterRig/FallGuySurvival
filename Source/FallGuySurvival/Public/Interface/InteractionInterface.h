// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FALLGUYSURVIVAL_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FText GetInteractionText();
	FText GetInteractionText_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(class ATFCharacter* Caller);
	void Interact_Implementation(class ATFCharacter* Caller);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsInteractable() const;
	bool IsInteractable_Implementation() const;
};
