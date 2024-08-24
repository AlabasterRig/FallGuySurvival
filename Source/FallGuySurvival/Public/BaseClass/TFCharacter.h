// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/SaveActorInterface.h"
#include "TFCharacter.generated.h"

UCLASS()
class FALLGUYSURVIVAL_API ATFCharacter : public ACharacter, public ISaveActorInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess = "true"))
	FGuid SaveActorID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess = "true"))
	class UStatlineComponent* Statline;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true"))
	bool WasSpawned = false;

public:
	// Sets default values for this character's properties
	ATFCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool CanJump() const;
	void HasJumped();
	bool CanSprint() const;
	void SetSprinting(const bool& IsSprinting);
	void SetSneaking(const bool& IsSneaking);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FGuid GetActorSaveID_Implementation();
	FSaveActorData GetSaveData_Implementation();

};
