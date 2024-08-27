// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveActorInterface.generated.h"

USTRUCT(BlueprintType)
struct FSaveComponentsData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UClass* ComponentClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> RawData;

};


USTRUCT(BlueprintType)
struct FSaveActorData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FTransform ActorTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<uint8> ByteData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FSaveComponentsData> ComponentData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool WasSpawned = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UClass* ActorClass;
};

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
	void SetActorGuid_Implementation(const FGuid& NewGuid);
	UFUNCTION(BlueprintNativeEvent)
	FSaveActorData GetSaveData();
	virtual FSaveActorData GetSaveData_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	FSaveComponentsData GetComponentSaveData();
	virtual FSaveComponentsData GetComponentSaveData_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void SetComponentSaveData(FSaveComponentsData Data);
	virtual void SetComponentSaveData_Implementation(FSaveComponentsData Data);

};
