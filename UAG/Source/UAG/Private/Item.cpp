// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UAG/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// ItemMeshComponent: 기본 생성을 위한 내부 이름.
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	
	// 새로 만든 메시의 주소를 저장하기 위해 루트 컴포넌트를 재할당한다.
	// 이전 루트 컴포넌트가 저장하고 있던 주소는 자동으로 삭제되고 itemMesh 의 주소로 설정된다.
	// 가비지 컬렉션이 루트 컴포넌트가 더이상 이전 주소를 가리키지 않는다는 것을 확인하기 때문.
	RootComponent = itemMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

float AItem::TransformedSin()
{
	return amplitude * FMath::Sin(runningTime * timeConstant);
}

float AItem::TransformedCos()
{
	return amplitude * FMath::Cos(runningTime * timeConstant);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	runningTime += DeltaTime;
}

 