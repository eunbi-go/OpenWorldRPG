// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "Chaos/ChaosGameplayEventDispatcher.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;

UCLASS()
class UAG_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	ABreakableActor();

	virtual void Tick(float DeltaTime) override;

	virtual void GetHit(const FVector& _impactPoint) override;

	UFUNCTION()
	void OnChaosBreak(const FChaosBreakEvent& BreakEvent);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UGeometryCollectionComponent* geometryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* capsuleComp;

private:
	

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ATreasure>> treasureArray;

	bool isBroken = false;
};
