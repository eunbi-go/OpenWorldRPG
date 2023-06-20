// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UAG/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	FVector location = GetActorLocation();
	FVector forward = GetActorForwardVector();
	
	DRAW_SPHERE(location);
	DRAW_LINE(location, location + forward * 100.f);
	DRAW_POINT(location + forward * 100.f);
	//DRAW_VECTOR(location, location + forward * 100.f);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

