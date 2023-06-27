// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UAG/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// ItemMeshComponent: �⺻ ������ ���� ���� �̸�.
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	
	// ���� ���� �޽��� �ּҸ� �����ϱ� ���� ��Ʈ ������Ʈ�� ���Ҵ��Ѵ�.
	// ���� ��Ʈ ������Ʈ�� �����ϰ� �ִ� �ּҴ� �ڵ����� �����ǰ� itemMesh �� �ּҷ� �����ȴ�.
	// ������ �÷����� ��Ʈ ������Ʈ�� ���̻� ���� �ּҸ� ����Ű�� �ʴ´ٴ� ���� Ȯ���ϱ� ����.
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

 