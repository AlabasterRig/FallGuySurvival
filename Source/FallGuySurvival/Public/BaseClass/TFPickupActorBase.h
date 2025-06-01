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

	UPROPERTY()
	FTimerHandle PhysicsTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WorldMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<class UItemBase> InventoryItem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int ItemCount = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText InteractionText = FText::FromString("DEFAULT");
	 
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	FText GetInteractionText_Implementation() override;
	void Interact_Implementation(class ATFCharacter* Caller) override;
	bool IsInteractable_Implementation() const override;

	UFUNCTION(BlueprintCallable)
	void SetWorldMesh(UStaticMesh* Mesh);
	UFUNCTION(BlueprintCallable)
	void SetInventoryItem(TSubclassOf<class UItemBase> Item);

	UFUNCTION()
	void StopPhysics();
};
