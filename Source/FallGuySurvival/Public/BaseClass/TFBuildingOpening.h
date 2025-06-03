// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFActor.h"
#include "Interface/InteractionInterface.h"
#include "TFBuildingOpening.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API ATFBuildingOpening : public ATFActor, public IInteractionInterface
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, meta = (AllowPrivateAccess = "true"))
	bool bIsOpen = false;

public:

	void SetParent(const class ATFBuildingBase* ParentBuilding);
	bool GetIsClosed() const;

	FText GetInteractionText_Implementation() override;
	void Interact_Implementation(class ATFCharacter* Caller) override;
	bool IsInteractable_Implementation() const override;
};
