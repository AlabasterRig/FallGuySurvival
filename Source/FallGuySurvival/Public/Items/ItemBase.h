// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/FSalvageItem.h"
#include "Data/FItemUIData.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API UItemBase : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText ItemName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText ItemDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int MaxStackSize = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	int CurrentStackSize = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FSalvageItem> ResourceTags;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* WorldMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float ItemWeight = 1.0;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnUse(class ATFCharacter* Caller) { };

	UFUNCTION(BlueprintCallable)
	float GetStackWeight() const { return ItemWeight * CurrentStackSize; }
	UFUNCTION(BlueprintCallable)
	float GetItemWeight() const { return ItemWeight; }
	UFUNCTION(BlueprintCallable)
	FItemUIData GetUIData() const { return FItemUIData(ItemName, ItemDescription, ItemIcon); }
	UFUNCTION(BlueprintCallable)
	TArray<FSalvageItem> GetSalvageData() const { return ResourceTags; }
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetWorldPickupMesh() const { return WorldMesh; }
	UFUNCTION(BlueprintCallable)
	int GetMaxStack() const { return MaxStackSize; }
	UFUNCTION(BlueprintCallable)
	int GetCurrentStack() const { return CurrentStackSize; }
	UFUNCTION(BlueprintCallable)
	int AddToStack(const int& Amount);
	UFUNCTION(BlueprintCallable)
	int RemoveFromStack(const int& Amount);
	UFUNCTION(BlueprintCallable)
	void SetStackSize(const int& Amount) { CurrentStackSize = Amount; }
};
