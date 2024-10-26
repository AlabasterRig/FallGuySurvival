// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFRandomizedMaterialActor.h"
#include "TF_Utils.h"

// Sets default values
ATFRandomizedMaterialActor::ATFRandomizedMaterialActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("World Mesh"));
	WorldMesh->SetupAttachment(RootComponent);
}

void ATFRandomizedMaterialActor::OnConstruction(const FTransform& Transform)
{
	if (!bRandomize || RandomizedMaterials.Num() <= 0)
	{
		return;
	}

	int RandSeed = RandomIntFromVector(RandomizationVector, Transform.GetLocation());  // Helper Function from TF_Utils used
	FRandomStream RandomStream;
	RandomStream.Initialize(RandSeed);

	TArray<int> Keys;
	RandomizedMaterials.GetKeys(Keys);
	for (int i = Keys[0]; i < RandomizedMaterials.Num(); i++)
	{
		if (RandomizedMaterials[i].Materials.Num() < 1)
		{
			continue;
		}
		int idx = RandomStream.RandRange(0, RandomizedMaterials[i].Materials.Num() - 1);
		WorldMesh->SetMaterial(i, RandomizedMaterials[i].Materials[idx]);
	}
}

// Called when the game starts or when spawned
void ATFRandomizedMaterialActor::BeginPlay()
{
	Super::BeginPlay();
	
}

