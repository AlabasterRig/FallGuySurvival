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
	
	FGuid SaveID;

public:	
	// Sets default values for this actor's properties
	ATFActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FGuid GetActorSaveID_Implementation();
	void SetActorGuid_Implementation(const FGuid& NewGuid);
	virtual FSaveActorData GetSaveData_Implementation();
};
