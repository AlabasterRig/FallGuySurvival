// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseClass/TFPlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/SphereComponent.h"
#include "Interface/InteractionInterface.h"
#include "Logger.h"

void ATFPlayerCharacter::TraceForInteraction()
{
	FCollisionQueryParams LineTraceP = FCollisionQueryParams(FName(TEXT("InteractionTrace")), true, this);
	LineTraceP.bReturnPhysicalMaterial = false;
	LineTraceP.bReturnFaceIndex = false;
	GetWorld()->DebugDrawTraceTag = TEXT("InteractionTrace"); // Debug
	FHitResult LTHit(ForceInit);
	FVector LTStart = FollowCamera->GetComponentLocation();
	float SearchLength = (FollowCamera->GetComponentLocation() - CameraBoom->GetComponentLocation()).Length();
	SearchLength += InteractionTraceLength;
	FVector LTEnd = (FollowCamera->GetForwardVector() * SearchLength) + LTStart;

	GetWorld()->LineTraceSingleByChannel(LTHit, LTStart, LTEnd, ECC_Visibility, LineTraceP);

	if (!LTHit.bBlockingHit || !LTHit.GetActor()->Implements<UInteractionInterface>())
	{
		InteractionActor = nullptr;
		return;
	}
	InteractionActor = LTHit.GetActor();
}

void ATFPlayerCharacter::Move(const FInputActionValue& Value)
{
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
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATFPlayerCharacter::Playerjump()
{
	if (ATFCharacter::CanJump() && !GetMovementComponent()->IsFalling())
	{
		ATFCharacter::HasJumped();
	}
}

void ATFPlayerCharacter::SprintOn()
{
	SetSprinting(true);
}

void ATFPlayerCharacter::SprintOff()
{
	SetSprinting(false);
}

void ATFPlayerCharacter::SneakOn()
{
	SetSneaking(true);
}

void ATFPlayerCharacter::SneakOff()
{
	SetSneaking(false);
}

void ATFPlayerCharacter::OnInteract()
{
	if (InteractionActor == nullptr)
	{
		return;
	}
	IInteractionInterface* Inter = Cast<IInteractionInterface>(InteractionActor);
	if (Inter == nullptr)
	{
		Logger::GetInstance()->AddMessage("ATFPlayerCharacter::OnInteract - Failed to cast to InteractionInterface", ErrorLevel::EL_ERROR);
		return;
	}
	//Inter->Interact_Implementation(this);
	Inter->Execute_Interact(InteractionActor, this);
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
	}
}


void ATFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	SaveActorID.Invalidate(); // Do not want Id to be a valid Guid
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

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Trigger Value"));
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

void ATFPlayerCharacter::OnInteractionTriggerOverlapEnd(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (!OtherActor->Implements<UInteractionInterface>())
	{
		return;
	}
	InteractableActors.Remove(OtherActor);
	bEnableRayTrace = InteractableActors.Num() > 0;
}

void ATFPlayerCharacter::UpdateInteractionText_Implementation()
{
	UpdateInteractionText();
}
