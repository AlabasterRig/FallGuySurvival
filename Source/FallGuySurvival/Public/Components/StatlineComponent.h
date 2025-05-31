// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/SaveActorInterface.h"
#include "Logger.h"
#include "Data/FCoreStat.h"
#include "Data/ECoreStat.h"
#include "StatlineComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLGUYSURVIVAL_API UStatlineComponent : public UActorComponent, public ISaveActorInterface
{
	GENERATED_BODY()

private:

#pragma region Stats

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Hunger = FCoreStat(100, 100, -0.125);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Statline|Stats", meta = (AllowPrivateAccess = "true"))
	FCoreStat Thirst = FCoreStat(100, 100, -0.25);

	void TickStats(const float& DeltaTime);
	void TickStamina(const float& DeltaTime);
	void TickHunger(const float& DeltaTime);
	void TickThirst(const float& DeltaTime);

#pragma endregion

#pragma region Moving

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsSprinting = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsSneaking = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SprintCostMultiplier = 2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SprintRegenerationPerSecond = 7;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float JumpCost = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 175;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 500;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SneakSpeed = 80;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float SecondsForStaminaExhaustion = 2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float CurrentStaminaExhaustion = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float StarvingHealthDamagePerSecond = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Movement", meta = (AllowPrivateAccess = "true"))
	float DehydrationHealthDamagePerSecond = 1;

	bool IsValidSpriting();
	class UCharacterMovementComponent* OwningCharacterMovementComp;

#pragma endregion

#pragma region Temperature

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	bool bConcernedAboutTemperature = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float CurrentAmbientTemp = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float CurrentLocalTempOffset = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float CurrentBodyTemperature = 36.6f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float HeatInsulation = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float ColdInsulation = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float BodyCoverage = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float AdjustmentFactoral = 500.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Statline|Temperature", meta = (AllowPrivateAccess = "true"))
	float TemperatureDifferenceToIgnore = 5.0f;

	void UpdateBodyTemperature(const float& DeltaTime);

#pragma endregion
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UStatlineComponent();

	UFUNCTION(BlueprintCallable)
	void SetMovementCompReference(UCharacterMovementComponent* Comp);

	UFUNCTION(BlueprintCallable)
	float GetStatPercentile(const ECoreStat stat) const;
	UFUNCTION(BlueprintCallable)
	bool CanSprint() const;
	UFUNCTION(BlueprintCallable)
	void SetSprinting(const bool& IsSprinting);
	UFUNCTION(BlueprintCallable)
	bool CanJump();
	UFUNCTION(BlueprintCallable)
	void HasJumped();
	UFUNCTION(BlueprintCallable)
	void SetSneaking(const bool& IsSneaking);

	virtual FSaveComponentsData GetComponentSaveData_Implementation();
	void SetComponentSaveData_Implementation(FSaveComponentsData Data);

	UFUNCTION(BlueprintCallable)
	void AdjustStat(const ECoreStat& Stat, const float& Amount);
	UFUNCTION(BlueprintCallable)
	void AdjustLocalTempOffset(const float& OffsetValue);
	UFUNCTION()
	void OnWorldTempChange(float Temperature);

	// TODO: Remove BlueprintCallable on Below three adjust functions once debugging is completed
	UFUNCTION(BlueprintCallable)
	void AdjustHeatInsulation(const float& Amount);
	UFUNCTION(BlueprintCallable)
	void AdjustColdInsulation(const float& Amount);
	UFUNCTION(BlueprintCallable)
	void AdjustBodyCoverage(const float& Amount);
};
