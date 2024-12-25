// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/TFActor.h"
#include "Interface/InteractionInterface.h"
#include "TFHeatSourceActor.generated.h"

UCLASS()
class FALLGUYSURVIVAL_API ATFHeatSourceActor : public ATFActor, public IInteractionInterface
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* HeatZone;  
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WorldMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCurveFloat* HeatFalloff;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleEmitter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Heat", meta = (AllowPrivateAccess = "true"))
	float MaxHeatValue = 27;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Heat", meta = (AllowPrivateAccess = "true"))
	float SphereRadius = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG", meta = (AllowPrivateAccess = "true"))
	float DEBUG_AppliedHeat = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heat", meta = (AllowPrivateAccess = "true"))
	bool bInteractableHeatSource = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Heat", meta = (AllowPrivateAccess = "true"))
	bool bIsActivated = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heat", meta = (AllowPrivateAccess = "true"))
	bool bUsesFuel = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heat", meta = (AllowPrivateAccess = "true"))
	FText EnableText = FText::FromString("Ignite");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heat", meta = (AllowPrivateAccess = "true"))
	FText DisableText = FText::FromString("Extinguish");
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Heat|Actors", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> ActorsInRange;
	
	ATFHeatSourceActor();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHeatZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnHeatZoneOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyindex);

	FText GetInteractionText_Implementation() override;
	void Interact_Implementation(class ATFCharacter* Caller) override;
	bool IsInteractable_Implementation() const override;

	virtual void UpdateFromSave_Implementation() override;
};
