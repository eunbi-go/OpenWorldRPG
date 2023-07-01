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

UCLASS()
class UAG_API AAGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAGCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* mappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* movementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* lookAction;

	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* cameraComp;
};
