// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSaveComponentsData.generated.h"

USTRUCT(BlueprintType)
struct FSaveComponentsData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UClass* ComponentClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> RawData;

};
