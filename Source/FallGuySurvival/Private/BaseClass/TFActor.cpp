// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFActor.h"

// Sets default values
ATFActor::ATFActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SaveID = FGuid::NewGuid();
}

// Called when the game starts or when spawned
void ATFActor::BeginPlay()
{
	Super::BeginPlay();
	if (!SaveID.IsValid())
	{
		SaveID = FGuid::NewGuid();
	}
}

// Called every frame
void ATFActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FGuid ATFActor::GetActorSaveID_Implementation()
{
	return SaveID;
}

void ATFActor::SetActorGuid_Implementation(const FGuid& NewGuid)
{
	if (SaveID.IsValid())
	{
		SaveID.Invalidate();
	}
	SaveID = NewGuid;
}

FSaveActorData ATFActor::GetSaveData_Implementation()
{
	FSaveActorData Ret;
	Ret.ActorTransform = this->GetActorTransform();
	Ret.ActorClass = this->GetClass();
	Ret.WasSpawned = bWasSpawned;
	return Ret;
}

void ATFActor::UpdateFromSave_Implementation()
{
	//UpdateFromSave();
	Execute_UpdateFromSave(this);
}

