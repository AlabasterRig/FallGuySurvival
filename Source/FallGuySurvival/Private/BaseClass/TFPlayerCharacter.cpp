// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseClass/TFPlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"  
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interface/InteractionInterface.h"
#include "Logger.h"


void ATFPlayerCharacter::TraceForInteraction()
{
	if (BlockCharacterInput())
	{
		return;
	}
	FCollisionQueryParams LTParams = FCollisionQueryParams(FName(TEXT("InteractionTrace")), true, this);
	LTParams.bReturnPhysicalMaterial = false;
	LTParams.bReturnFaceIndex = false;
	GetWorld()->DebugDrawTraceTag = DEBUG_SHOW_INTERACTION_TRACE ? TEXT("InteractionTrace") : TEXT("NONE");
	FHitResult LTHit(ForceInit);
	FVector LTStart, LTEnd;
	float SearchLength;
	if (!bIsFirstPerson)
	{
		LTStart = FollowCamera->GetComponentLocation();
		SearchLength = (FollowCamera->GetComponentLocation() - CameraBoom->GetComponentLocation()).Length();
		SearchLength += InteractionTraceLength;
		LTEnd = (FollowCamera->GetForwardVector() * SearchLength) + LTStart;
	}
	else {
		LTStart = FirstPersonCamera->GetComponentLocation();
		SearchLength = (FirstPersonCamera->GetComponentLocation() - CameraBoom->GetComponentLocation()).Length();
		SearchLength += InteractionTraceLength;
		LTEnd = (FirstPersonCamera->GetForwardVector() * SearchLength) + LTStart;
	}

	GetWorld()->LineTraceSingleByChannel(LTHit, LTStart, LTEnd, ECC_Visibility, LTParams);
	UpdateInteractionText_Implementation();
	if (!LTHit.bBlockingHit || !LTHit.GetActor()->Implements<UInteractionInterface>())
	{
		InteractionActor = nullptr;
		return;
	}
	InteractionActor = LTHit.GetActor();
}

bool ATFPlayerCharacter::BlockCharacterInput() const
{
	return bInventoryIsShown;
}

void ATFPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (BlockCharacterInput())
	{
		return;
	}
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATFPlayerCharacter::Look(const FInputActionValue& Value)
{
	if (BlockCharacterInput())
	{
		return;
	}
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATFPlayerCharacter::Playerjump()
{
	if (BlockCharacterInput())
	{
		return;
	}
	if (ATFCharacter::CanJump() && !GetMovementComponent()->IsFalling())
	{
		ATFCharacter::HasJumped();
	}
}

void ATFPlayerCharacter::SprintOn()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSprinting(true);
}

void ATFPlayerCharacter::SprintOff()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSprinting(false);
}

void ATFPlayerCharacter::SneakOn()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSneaking(true);
}

void ATFPlayerCharacter::SneakOff()
{
	if (BlockCharacterInput())
	{
		return;
	}
	SetSneaking(false);
}

void ATFPlayerCharacter::OnInteract()
{
	if (BlockCharacterInput())
	{
		return;
	}
	if (InteractionActor == nullptr)
	{
		return;
	}
	IInteractionInterface* Inter = Cast<IInteractionInterface>(InteractionActor);
	if (Inter == nullptr)
	{
		Logger::GetInstance()->AddMessage("ATFPlayerCharacter::OnInteract - Failed to Cast to InteractionInterface", ErrorLevel::EL_ERROR);
		return;
	}
	Inter->Execute_Interact(InteractionActor, this);
}

void ATFPlayerCharacter::TogglePerspective()
{
	bIsFirstPerson = !bIsFirstPerson;
	if (!bIsFirstPerson)
	{
		//bIsFirstPerson = false;
		FirstPersonCamera->Deactivate();
		FollowCamera->Activate();
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;
		return;
	}
	bIsFirstPerson = true;
	FollowCamera->Deactivate();
	FirstPersonCamera->Activate();
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	return;
}

void ATFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATFPlayerCharacter::Playerjump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATFPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATFPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ATFPlayerCharacter::SprintOn);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATFPlayerCharacter::SprintOff);
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Started, this, &ATFPlayerCharacter::SneakOn);
		EnhancedInputComponent->BindAction(SneakAction, ETriggerEvent::Completed, this, &ATFPlayerCharacter::SneakOff);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ATFPlayerCharacter::OnInteract);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Completed, this, &ATFPlayerCharacter::TogglePlayerInventory_Implementation);
		EnhancedInputComponent->BindAction(ToggleCameraPerspective, ETriggerEvent::Completed, this, &ATFPlayerCharacter::TogglePerspective);
	}
}

void ATFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SaveActorID.Invalidate();
}

ATFPlayerCharacter::ATFPlayerCharacter()
{	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;	
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), "head");
	FirstPersonCamera->SetRelativeRotation(FRotator(0, -90, 90));
	FirstPersonCamera->SetRelativeLocation(FVector(15, 20, 2.5));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->Deactivate();
	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Trigger Volume"));
	InteractionTrigger->SetupAttachment(RootComponent);
	InteractionTrigger->SetRelativeScale3D(FVector(10));
	InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATFPlayerCharacter::OnInteractionTriggerOverlapBegin);
	InteractionTrigger->OnComponentEndOverlap.AddDynamic(this, &ATFPlayerCharacter::OnInteractionTriggerOverlapEnd);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
}

void ATFPlayerCharacter::Tick(float DeltaTime)
{
	if (bEnableRayTrace)
	{
		TraceForInteraction();
	}
	// AddExperiencePoints(100); // TODO: When experience points added to assets, then enable 
}

void ATFPlayerCharacter::PlayerLevelUp()
{
	while (ExperiencePointsReceivedOnPickup >= ExperiencePointsRequired)
	{
		CurrentLevel += 1;
		ExperiencePointsReceivedOnPickup -= ExperiencePointsRequired;
		if (CurrentLevel >= 35)
		{
			float NewExperienceRequired = ExperiencePointsRequired * 0.1;
			ExperiencePointsRequired += NewExperienceRequired;
		}
		else
		{
			float NewExperienceRequired = ExperiencePointsRequired * 0.2;
			ExperiencePointsRequired += NewExperienceRequired;
		}
	}
}

void ATFPlayerCharacter::AddExperiencePoints(const float& ExperiencePoints)
{
	ExperiencePointsReceivedOnPickup += ExperiencePoints;
	PlayerLevelUp();
}

void ATFPlayerCharacter::OnInteractionTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UInteractionInterface>())
	{
		return;
	}
	InteractableActors.Add(OtherActor);
	bEnableRayTrace = true;
}

void ATFPlayerCharacter::OnInteractionTriggerOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyindex)
{
	if (!OtherActor->Implements<UInteractionInterface>())
	{
		return;
	}
	InteractableActors.Remove(OtherActor);
	bEnableRayTrace = InteractableActors.Num() > 0;
	if (!bEnableRayTrace)
	{
		TraceForInteraction();
		UpdateInteractionText_Implementation();
	}
}

void ATFPlayerCharacter::UpdateInteractionText_Implementation()
{
	UpdateInteractionText();
}

void ATFPlayerCharacter::TogglePlayerInventory_Implementation()
{
	bInventoryIsShown = !bInventoryIsShown;
	TogglePlayerInventory();
}
