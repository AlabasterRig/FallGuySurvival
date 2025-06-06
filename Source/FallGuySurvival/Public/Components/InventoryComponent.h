// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/SaveActorInterface.h"
#include "Data/FItemUIData.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLGUYSURVIVAL_API UInventoryComponent : public UActorComponent, public ISaveActorInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	float MaxWeight = 100;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	float CurrentWeight = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UItemBase>> InventoryContents;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ATFCharacter* OwnerCharacter = nullptr;

	// Helper Function
	UFUNCTION(BlueprintCallable)
	bool IsOverCarryWeight(const float& ItemWeight) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool AddItemToTop(TSubclassOf<class UItemBase> Item);
	UFUNCTION(BlueprintCallable)
	bool AddItemAtIndex(TSubclassOf<class UItemBase> Item, int& Index);
	UFUNCTION(BlueprintCallable)
	bool AddItemToStackAtIndex(TSubclassOf<class UItemBase> Item, const int& Index);

	UFUNCTION(BlueprintCallable)
	TArray<FItemUIData> GetInventoryUIData() const;

	UFUNCTION(BlueprintCallable)
	bool UseItemAtIndex(const int& Index);
	UFUNCTION(BlueprintCallable)
	bool DropStackAtIndex(const int& Index);
};
