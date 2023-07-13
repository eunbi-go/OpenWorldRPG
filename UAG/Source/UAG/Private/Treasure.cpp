// Fill out your copyright notice in the Description page of Project Settings.


#include "Treasure.h"
#include "Characters/AGCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATreasure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0.f, 0.f, DeltaTime * 45.f));
}

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAGCharacter* character = Cast<AAGCharacter>(OtherActor);
	if (character)
	{
		if (overlapSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				overlapSound,
				GetActorLocation()
			);
		}
		
		Destroy();
	}
}
