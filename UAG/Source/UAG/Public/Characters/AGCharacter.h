// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AGCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class AItem;

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

	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);
	void Equip(const FInputActionValue& _value);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* cameraComp;

	UPROPERTY(VisibleInstanceOnly)
	AItem* overlappingItem;

public:
	// FORCEINLINE: 함수를 강제로 인라인화시킴.
	FORCEINLINE void SetOverlappingItem(AItem* _item) { overlappingItem = _item; }
};
