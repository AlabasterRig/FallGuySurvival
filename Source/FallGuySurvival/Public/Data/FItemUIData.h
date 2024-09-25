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
	UTexture2D* ItemIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int StackSize = 0;

	FItemUIData()
	{

	}

	FItemUIData(const int& Index, const FText& name, const FText& description, UTexture2D* icon, const int& Count)
	{
		ItemIndex = Index;
		ItemName = name;
		ItemDescription = description;
		this->ItemIcon = icon;
		StackSize = Count;
	};

};
