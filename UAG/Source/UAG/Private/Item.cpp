// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UAG/DebugMacros.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// ItemMeshComponent: �⺻ ������ ���� ���� �̸�.
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	
	// ���� ���� �޽��� �ּҸ� �����ϱ� ���� ��Ʈ ������Ʈ�� ���Ҵ��Ѵ�.
	// ���� ��Ʈ ������Ʈ�� �����ϰ� �ִ� �ּҴ� �ڵ����� �����ǰ� itemMesh �� �ּҷ� �����ȴ�.
	// ������ �÷����� ��Ʈ ������Ʈ�� ���̻� ���� �ּҸ� ����Ű�� �ʴ´ٴ� ���� Ȯ���ϱ� ����.
	RootComponent = itemMesh;

	// USphereComponent: UPrimitiveComponent ���.
	// UPrimitiveComponent: ComponentBeginOverlap ���� ��������Ʈ ����.
	// ��������Ʈ �Ű�������
	// 1. UPrimitiveComponent: �Է� ����, �� ������ ��������Ʈ�� ���ε��� �� �ִ� �ݹ� ���� ����
	// 2. OnComponentBeginOverlap: ��������Ʈ �̸�
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	sphereComp->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	// 1. �ݹ� �Լ��� �ִ� ��ü�� ���� ������
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

float AItem::TransformedSin()
{
	return amplitude * FMath::Sin(runningTime * timeConstant);
}

float AItem::TransformedCos()
{
	return amplitude * FMath::Cos(runningTime * timeConstant);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FString otherActorName = OtherActor->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, otherActorName);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const FString otherActorName = FString("Ending Overlap: ") + OtherActor->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Blue, otherActorName);
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	runningTime += DeltaTime;
}

 