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

	// ������ ����X �� �ƴ� ����X �������� �̵��Ѵ�.
	// �̷��� �̵� ����� ������:
	// �� �����Ӹ��� ���� �������� �߰��ϰ� ������ ������ �ӵ��� �������� �ʰ�, ����� �� �ִ�.
	// �����ӿ� ���� ���Ͱ� ������ �ӵ��� �������� ���� �� �ִ�.
	// �ذ� ���: DeltaTime ���� ������ ���� �󸶳� ���� �ð��� �������� �˷��ش�.
	
	//// ����
	//AddActorWorldOffset(FVector(1.f, 0.f, 0.f));

	// ����
	// movement rate in units of cm/s
	float movementRate = 50.f;

	// movementRate * DeltaTime : (cm/s) * (s/frame) = (cm/frame)
	// -> �����ӿ� ������� ������ �ӵ��� �̵��Ѵ�.
	// ����: �̵� ������ �ӵ��� ���������� ����� DeltaTime���� �̵��ϱ� ����.
	// -> DeltaTime�� �̿��Ͽ� �̵� ũ�⸦ �����ؾ� �Ѵ�.
	// ������ �߰��� ���� ����� �����ϸ� �������� ������ �� �ִ�.
	// ���� �̸� �����ϱ� ���� DeltaTime ���� Ȯ���ϴ� ���� �߿��ϴ�.
	// �̵� �ӵ� - ������ �ӵ�: ���������� ����! ������ �ӵ��� ���� �̵��ӵ��� �������� �ʰ�
	
	AddActorWorldOffset(FVector(movementRate * DeltaTime, 0.f, 0.f));

	float rotationRate = 45.f;

	AddActorWorldRotation(FRotator(0.f, rotationRate * DeltaTime, 0));

	DRAW_SPHERE_SINGLE_FRAME(GetActorLocation());
	DRAW_VECTOR_SINGLE_FRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
}

