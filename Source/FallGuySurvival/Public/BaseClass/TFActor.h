// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SaveActorInterface.h"
#include "TFActor.generated.h"

UCLASS()
class FALLGUYSURVIVAL_API ATFActor : public AActor, public ISaveActorInterface
{
	GENERATED_BODY()

private:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid SaveID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bWasSpawned = false;

	virtual void BeginPlay() override;

public:	
	ATFActor();

	virtual void Tick(float DeltaTime) override;

	virtual FGuid GetActorSaveID_Implementation();
	void SetActorGuid_Implementation(const FGuid& NewGuid);
	virtual FSaveActorData GetSaveData_Implementation();
	virtual void UpdateFromSave_Implementation();
};
