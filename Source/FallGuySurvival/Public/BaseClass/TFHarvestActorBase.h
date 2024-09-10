// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFActor.h"
#include "Interface/InteractionInterface.h"
#include "TFHarvestActorBase.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API ATFHarvestActorBase : public ATFActor, public IInteractionInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PermanentMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<class AActor> InventoryItem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText InteractionText = FText::FromString("DEFAULT");

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HarvestMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	bool bIsHarvested = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int ItemCount = 1;

public:
	UFUNCTION(BlueprintCallable)
	FText GetInteractionText_Implementation();
	void Interact_Implementation(class ATFCharacter* Caller);
	bool IsInteractable_Implementation() const;
};
