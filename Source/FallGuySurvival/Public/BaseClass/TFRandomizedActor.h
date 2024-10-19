 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ERandomizedVector.h"
#include "TFRandomizedActor.generated.h"

UCLASS()
class FALLGUYSURVIVAL_API ATFRandomizedActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomize", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> ActorOptions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Randomize", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WorldMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomize", meta = (AllowPrivateAccess = "true"))
	ERandomizedVector RandomizationVector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnConstruction(const FTransform& Transform) override;

public:	
	ATFRandomizedActor();

};
