// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FItemUIData.generated.h"

USTRUCT(BlueprintType)
struct FItemUIData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ItemIndex = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText ItemName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText ItemDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText UseText;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bUsable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int StackSize = 1;

	FItemUIData()
	{

	}

	FItemUIData(const int& Index, const FText& name, const FText& description, const FText& useText, const bool& useable, UTexture2D* icon, const int& Count)
	{
		ItemIndex = Index;
		ItemName = name;
		ItemDescription = description;
		UseText = useText;
		bUsable = useable;
		this->ItemIcon = icon;
		StackSize = Count;
	};

};
