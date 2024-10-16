// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/FSaveActorData.h"
#include "SaveActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FALLGUYSURVIVAL_API ISaveActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	FGuid GetActorSaveID();  // Blueprint Version
	virtual FGuid GetActorSaveID_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void SetActorGuid(const FGuid& NewGuid);
	virtual void SetActorGuid_Implementation(const FGuid& NewGuid);
	UFUNCTION(BlueprintNativeEvent)
	FSaveActorData GetSaveData();
	virtual FSaveActorData GetSaveData_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void UpdateFromSave();
	virtual void UpdateFromSave_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	FSaveComponentsData GetComponentSaveData();
	virtual FSaveComponentsData GetComponentSaveData_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void SetComponentSaveData(FSaveComponentsData Data);
	virtual void SetComponentSaveData_Implementation(FSaveComponentsData Data);
	UFUNCTION(BlueprintNativeEvent)
	void SetActorRawSaveData(const TArray<FString>& Data);
	virtual void SetActorRawSaveData_Implementation(const TArray<FString>& Data);
};
