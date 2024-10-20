// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFRandomizedActor.h"
#include "TF_Utils.h"

// Sets default values
ATFRandomizedActor::ATFRandomizedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("World Mesh"));
	WorldMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATFRandomizedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATFRandomizedActor::OnConstruction(const FTransform& Transform)
{
	if (ActorOptions.Num() <= 0)
	{
		// TODO: Log Error
		return;
	}

	if (OverrideRandomization && OverrideIndex <= ActorOptions.Num() - 1)
	{
		WorldMesh->SetStaticMesh(ActorOptions[OverrideIndex]);
		return;
	}
	
	int RandSeed = RandomIntFromVector(RandomizationVector, Transform.GetLocation());  // Helper Function from TF_Utils used

	FRandomStream RandomStream;
	RandomStream.Initialize(RandSeed);
	int idx = RandomStream.RandRange(0, ActorOptions.Num() - 1);
	WorldMesh->SetStaticMesh(ActorOptions[idx]);
}

