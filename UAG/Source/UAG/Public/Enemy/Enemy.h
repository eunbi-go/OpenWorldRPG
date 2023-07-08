// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

class UAnimMontage;

UCLASS()
class UAG_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void GetHit(const FVector& _impactPoint) override;

	void CalculateHitDegree(const FVector& _impactPoint);

protected:
	virtual void BeginPlay() override;
	
	// Play Montages
	void PlayHitMontages(const FName& _sectionName);

private:	
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* hitSound;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* hitParticle;
	
	// Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* hitMontage;
};
