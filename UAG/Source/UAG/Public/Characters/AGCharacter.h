// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "AGCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;


UCLASS()
class UAG_API AAGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAGCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* mappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* movementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* lookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* jumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* equipAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* attackAction;

	// callback for Input
	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);
	void Equip(const FInputActionValue& _value);
	void Attack(const FInputActionValue& _value);

	// Play Montage
	void PlayAttackMontage();
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	bool IsCanAttack();

private:
	ECharacterState characterState = ECharacterState::ECS_Unequipped;
	EActionState actionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* cameraComp;

	UPROPERTY(VisibleInstanceOnly)
	AItem* overlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* attackMontage;

public:
	// FORCEINLINE: �Լ��� ������ �ζ���ȭ��Ŵ.
	FORCEINLINE void SetOverlappingItem(AItem* _item) { overlappingItem = _item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return characterState; }
	FORCEINLINE void SetCharacterState(ECharacterState _state) { characterState = _state; }
	FORCEINLINE void SetActionState(EActionState _state) { actionState = _state; }
};
