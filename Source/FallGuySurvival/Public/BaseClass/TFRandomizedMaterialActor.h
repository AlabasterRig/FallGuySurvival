// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ERandomizedVector.h"
#include "TFRandomizedMaterialActor.generated.h"

USTRUCT(BlueprintType)
struct FMaterialArray
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UMaterialInterface*> Materials;
};

UCLASS()
class FALLGUYSURVIVAL_API ATFRandomizedMaterialActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Randomized Materials", meta = (AllowPrivateAccess = "true"))
	TMap<int, FMaterialArray> RandomizedMaterials;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Randomized Materials", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WorldMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Randomized Materials", meta = (AllowPrivateAccess = "true"))
	ERandomizedVector RandomizationVector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATFRandomizedMaterialActor();

	void OnConstruction(const FTransform& Transform) override;
};
