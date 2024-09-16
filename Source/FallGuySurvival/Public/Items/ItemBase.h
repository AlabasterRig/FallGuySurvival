// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

USTRUCT(BlueprintType)
struct FSalvageItem
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Quantity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Tag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UJunkItemBase> Item;
};

USTRUCT(BlueprintType)
struct FItemUIData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText ItemName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText ItemDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon;

	FItemUIData()
	{

	}

	FItemUIData(const FText& name, const FText& description, UTexture2D* icon)
	{
		ItemName = name;
		ItemDescription = description;
		this->ItemIcon = icon;
	};
};

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
	float GetStackWeight(const int Amount) const { return ItemWeight * Amount; }
	UFUNCTION(BlueprintCallable)
	float GetItemWeight() const { return ItemWeight; }
	UFUNCTION(BlueprintCallable)
	FItemUIData GetUIData() const { return FItemUIData(ItemName, ItemDescription, ItemIcon); }
	UFUNCTION(BlueprintCallable)
	TArray<FSalvageItem> GetSalvageData() const { return ResourceTags; }
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetWorldPickupMesh() const { return WorldMesh; }
	UFUNCTION(BlueprintCallable)
	int GetMaxStackSize() const { return MaxStackSize; }
};
