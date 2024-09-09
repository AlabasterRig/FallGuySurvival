// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFActor.h"
#include "Interface/InteractionInterface.h"
#include "TFPickupActorBase.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API ATFPickupActorBase : public ATFActor, public IInteractionInterface
{
	GENERATED_BODY()
	
private:
	ATFPickupActorBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WorldMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<class AActor> InventoryItem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int ItemCount = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText InteractionText = FText::FromString("DEFAULT");
	 

public:
	FText GetInteractionText_Implementation();
	void Interact_Implementation(class ATFCharacter* Caller);
	bool IsInteractable_Implementation() const;
};
