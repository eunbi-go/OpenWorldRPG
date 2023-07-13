// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable/BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Treasure.h"
#include "Components/CapsuleComponent.h"


ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	geometryComp = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryComp"));
	SetRootComponent(geometryComp);
	geometryComp->SetGenerateOverlapEvents(true);
	geometryComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	geometryComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	geometryComp->bNotifyBreaks = true;
	geometryComp->bNotifyCollisions = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	capsuleComp->SetupAttachment(GetRootComponent());
	capsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	capsuleComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();

	geometryComp->SetNotifyBreaks(true);
	geometryComp->OnChaosBreakEvent.AddDynamic(this, &ABreakableActor::OnChaosBreak);
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakableActor::GetHit(const FVector& _impactPoint)
{
	if (isBroken)
		return;

	isBroken = true;
	UWorld* world = GetWorld();

	if (world && treasureArray.Num() > 0)
	{
		FVector location = GetActorLocation();
		location.Z += 75.f;

		int32 index = FMath::RandRange(0, treasureArray.Num() - 1);

		world->SpawnActor<ATreasure>(
			treasureArray[index],
			location,
			GetActorRotation()
			);

	}

	capsuleComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void ABreakableActor::OnChaosBreak(const FChaosBreakEvent& BreakEvent)
{
	SetLifeSpan(2.f);
}
