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
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 액터의 로컬X 가 아닌 월드X 방향으로 이동한다.
	// 이러한 이동 방식의 문제점:
	// 매 프레임마다 월드 오프셋을 추가하고 있지만 프레임 속도는 일정하지 않고, 변경될 수 있다.
	// 프레임에 따라 액터가 일정한 속도로 움직이지 않을 수 있다.
	// 해결 방법: DeltaTime 이전 프레임 이후 얼마나 많은 시간이 지났는지 알려준다.
	
	//// 이전
	//AddActorWorldOffset(FVector(1.f, 0.f, 0.f));

	// 이후
	// movement rate in units of cm/s
	float movementRate = 50.f;

	// movementRate * DeltaTime : (cm/s) * (s/frame) = (cm/frame)
	// -> 프레임에 상관없이 일정한 속도로 이동한다.
	// 이유: 이동 프레임 속도를 독립적으로 만드는 DeltaTime으로 이동하기 때문.
	// -> DeltaTime을 이용하여 이동 크기를 조절해야 한다.
	// 게임이 중간에 많은 계산을 수행하면 프레임이 떨어질 수 있다.
	// 따라서 이를 수용하기 위해 DeltaTime 으로 확장하는 것이 중요하다.
	// 이동 속도 - 프레임 속도: 독립적으로 존재! 프레임 속도에 따라 이동속도가 결정되지 않게
	
	AddActorWorldOffset(FVector(movementRate * DeltaTime, 0.f, 0.f));

	float rotationRate = 45.f;

	AddActorWorldRotation(FRotator(0.f, rotationRate * DeltaTime, 0));

	DRAW_SPHERE_SINGLE_FRAME(GetActorLocation());
	DRAW_VECTOR_SINGLE_FRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
}

