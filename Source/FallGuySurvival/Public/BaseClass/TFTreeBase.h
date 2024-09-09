// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFActor.h"
#include "BaseClass/TFPickupActorBase.h"
#include "TFTreeBase.generated.h"

class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class FALLGUYSURVIVAL_API ATFTreeBase : public ATFActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(SaveGame)
	bool bIsHarvested = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Health = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MainTreeMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TreeStumpMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class TSubclassOf<ATFPickupActorBase> LogPickupActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int NumberOfLogsToSpawn = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FTransform> SpawnActorTransforms;

	ATFTreeBase();
	void SetHarvestState();
	void Harvest();
	void SpawnPickups();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHarvestedBP();
	void OnHarvestedBP_Implementation();

	virtual FSaveActorData GetSaveData_Implementation() override;
	void UpdateFromSave_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
 