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
