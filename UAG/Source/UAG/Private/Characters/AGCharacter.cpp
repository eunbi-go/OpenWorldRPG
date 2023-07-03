// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item.h"
#include "Weapons/Weapon.h"

AAGCharacter::AAGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	JumpMaxCount = 2;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(GetRootComponent());
	springArmComp->TargetArmLength = 300.f;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComp"));
	cameraComp->SetupAttachment(springArmComp);
}

void AAGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(mappingContext, 0);
		}
	}
}

void AAGCharacter::Move(const FInputActionValue& _value)
{
	const FVector2D movement = _value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation = FRotator(0.f, rotation.Yaw, 0.f);

		const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(forwardDirection, movement.Y);

		const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(rightDirection, movement.X);
	}
}

void AAGCharacter::Look(const FInputActionValue& _value)
{
	const FVector2D lookAxisValue = _value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(lookAxisValue.X);
		AddControllerPitchInput(lookAxisValue.Y);
	}
}

void AAGCharacter::Equip(const FInputActionValue& _value)
{
	AWeapon* weapon = Cast<AWeapon>(overlappingItem);
	if (weapon)
	{
		weapon->Equip(GetMesh(), TEXT("RightHandSocket"));
		characterState = ECharacterState::ECS_EquippedOneHandWeapon;
	}
}

void AAGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(movementAction, ETriggerEvent::Triggered, this, &AAGCharacter::Move);
		enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AAGCharacter::Look);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Triggered, this, &AAGCharacter::Jump);
		enhancedInputComponent->BindAction(equipAction, ETriggerEvent::Triggered, this, &AAGCharacter::Equip);
	}
}

void AAGCharacter::Jump()
{
	Super::Jump();
}

