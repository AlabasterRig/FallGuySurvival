// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFTreeBase.h"
#include "Engine/DamageEvents.h"

ATFTreeBase::ATFTreeBase()
{
	MainTreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Tree Mesh"));
	MainTreeMesh->SetupAttachment(RootComponent);
	TreeStumpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree Stump Mesh"));
	TreeStumpMesh->SetupAttachment(RootComponent);
	TreeStumpMesh->bHiddenInGame = true; // Better performance, so that not many things are loaded in game.
	TreeStumpMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATFTreeBase::SetHarvestState()
{
	if (!bIsHarvested)
	{
		return;
	}
	MainTreeMesh->DestroyComponent();
	//MainTreeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//MainTreeMesh->bHiddenInGame = true;
	//TreeStumpMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//TreeStumpMesh->bHiddenInGame = false;
	//TreeStumpMesh->SetVisibility(true, true);
}

void ATFTreeBase::Harvest()
{
	bIsHarvested = true;
	// TODO: Add in PickUp Spwan logic here 
	SetHarvestState();
	OnHarvestedBP();
}

void ATFTreeBase::OnHarvestedBP_Implementation()
{
	OnHarvestedBP();
}

FSaveActorData ATFTreeBase::GetSaveData_Implementation()
{
	FSaveActorData Ret;
	Ret.ActorTransform = this->GetActorTransform();
	Ret.ActorClass = this->GetClass();
	Ret.WasSpawned = bWasSpawned;
	return Ret;
}

void ATFTreeBase::UpdateFromSave_Implementation()
{
	SetHarvestState();
}

float ATFTreeBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!DamageCauser->Tags.Contains("HarvestTree"))
	{
		return 0.0f;
	}
	Health -= DamageAmount;
	if (Health > 0.0f)
	{
		return 0.0f;
	}
	Harvest();
	return 0.0f;
}