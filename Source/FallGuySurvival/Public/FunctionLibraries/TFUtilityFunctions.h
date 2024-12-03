// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/ELogLevel.h"
#include "Logger.h"
#include "TFUtilityFunctions.generated.h"

/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API UTFUtilityFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static ErrorLevel LogLevelToErrorLevel(const ELogLevel& Level);

protected:

public:
	UFUNCTION(BlueprintCallable, Category = "Temperature")
	static float ConvertCelsiusToFahrenheit(const float& Celsius);
	UFUNCTION(BlueprintCallable, Category = "Logging")
	static void AddLogMessage(const FString& Message, const ELogLevel& Level);
};
