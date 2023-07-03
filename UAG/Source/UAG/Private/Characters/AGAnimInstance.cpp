// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AGAnimInstance.h"
#include "Characters/AGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAGAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	character = Cast<AAGCharacter>(TryGetPawnOwner());
	if (character)
	{
		movementComp = character->GetCharacterMovement();
	}
}

void UAGAnimInstance::NativeUpdateAnimation(float _deltaTime)
{
	Super::NativeUpdateAnimation(_deltaTime);

	if (movementComp)
	{
		groundSpeed = UKismetMathLibrary::VSizeXY(movementComp->Velocity);
		isFalling = movementComp->IsFalling();
	}
}
