// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFRandomizedActor.h"

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
	
	int RandSeed = 0;
	switch (RandomizationVector)
	{
	case ERandomizedVector::X:
		RandSeed = floor(Transform.GetLocation().X);
		break;
	case ERandomizedVector::Y:
		RandSeed = floor(Transform.GetLocation().Y);
		break;
	case ERandomizedVector::Z:
		RandSeed = floor(Transform.GetLocation().Z);
		break;
	case ERandomizedVector::XY:
		RandSeed = floor(Transform.GetLocation().X + Transform.GetLocation().Y);
		break;
	case ERandomizedVector::XZ:
		RandSeed = floor(Transform.GetLocation().X + Transform.GetLocation().Z);
		break;
	case ERandomizedVector::YZ:
		RandSeed = floor(Transform.GetLocation().Y + Transform.GetLocation().Z);
		break;
	case ERandomizedVector::XYZ:
		RandSeed = floor(Transform.GetLocation().X + Transform.GetLocation().Y + Transform.GetLocation().Z);
		break;
	default:
		break;
	}

	FRandomStream RandomStream;
	RandomStream.Initialize(RandSeed);
	int idx = RandomStream.RandRange(0, ActorOptions.Num() - 1);
	WorldMesh->SetStaticMesh(ActorOptions[idx]);
}

