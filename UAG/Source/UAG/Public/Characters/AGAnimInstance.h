// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "AGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UAG_API UAGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float _deltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AAGCharacter* character;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* movementComp;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float groundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement | Character State")
	ECharacterState characterState;

protected:
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_UnEquip();

	UFUNCTION()
	void AnimNotify_Equip();

	UFUNCTION()
	void AnimNotify_EquipEnd();
};