// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UAG/DebugMacros.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// ItemMeshComponent: 기본 생성을 위한 내부 이름.
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	
	// 새로 만든 메시의 주소를 저장하기 위해 루트 컴포넌트를 재할당한다.
	// 이전 루트 컴포넌트가 저장하고 있던 주소는 자동으로 삭제되고 itemMesh 의 주소로 설정된다.
	// 가비지 컬렉션이 루트 컴포넌트가 더이상 이전 주소를 가리키지 않는다는 것을 확인하기 때문.
	RootComponent = itemMesh;

	// USphereComponent: UPrimitiveComponent 상속.
	// UPrimitiveComponent: ComponentBeginOverlap 등의 델리게이트 존재.
	// 델리게이트 매개변수들
	// 1. UPrimitiveComponent: 입력 유형, 이 유형의 델리게이트에 바인딩될 수 있는 콜백 유형 결정
	// 2. OnComponentBeginOverlap: 델리게이트 이름
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	sphereComp->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	// 1. 콜백 함수가 있는 객체에 대한 포인터
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

 