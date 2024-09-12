// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/TFTreeBase.h"
#include "Engine/DamageEvents.h"

ATFTreeBase::ATFTreeBase()
{
	TreeStumpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree Stump Mesh"));
	TreeStumpMesh->SetupAttachment(RootComponent);
	TreeStumpMesh->bHiddenInGame = true; // Better performance, so that not many things are loaded in game.
	TreeStumpMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MainTreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Tree Mesh"));
	MainTreeMesh->SetupAttachment(TreeStumpMesh);
	MainTreeMesh->bHiddenInGame = false;
	MainTreeMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ATFTreeBase::SetHarvestState()
{
	if (!bIsHarvested)
	{
		return;
	}
	MainTreeMesh->DestroyComponent();
	TreeStumpMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TreeStumpMesh->bHiddenInGame = false;
	TreeStumpMesh->SetVisibility(true, true);
	MarkComponentsRenderStateDirty();
}

void ATFTreeBase::Harvest()
{
	bIsHarvested = true;
	SpawnPickups();
	SetHarvestState();
	OnHarvestedBP();
}

void ATFTreeBase::SpawnPickups()
{
	if (!IsValid(LogPickupActor))
	{
		return;
	}

	for (int i = 0; i < NumberOfLogsToSpawn; i++)
	{
		FVector TreeLoc = this->GetActorLocation();
		FTransform SpawnTreeTrans = SpawnActorTransforms[i];
		SpawnTreeTrans.SetLocation(SpawnTreeTrans.GetLocation() + TreeLoc);
		ATFPickupActorBase* Log = GetWorld()->SpawnActor<ATFPickupActorBase>(LogPickupActor, SpawnTreeTrans);
		if (IsValid(Log))
		{
			Log->SetActorTransform(SpawnTreeTrans);
			Log->SetWasSpawned(true);
		}
	}
}

void ATFTreeBase::OnHarvestedBP_Implementation()
{
	OnHarvestedBP();
}

FSaveActorData ATFTreeBase::GetSaveData_Implementation()
{
	return FSaveActorData(GetActorTransform(), bWasSpawned, GetClass());
}

void ATFTreeBase::UpdateFromSave_Implementation()
{
	SetHarvestState();
}

float ATFTreeBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsHarvested || !DamageCauser->Tags.Contains("HarvestTree"))
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
