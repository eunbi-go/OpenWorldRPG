// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	// LogTemp: ����� �������� ���� �߰�/���ŵǴ� �α׿� ���ȴ�.
	// Warning: �پ��� �α� ���� �� �ϳ�.
	UE_LOG(LogTemp, Warning, TEXT("Begin Play called"));

	if (GEngine)
	{
		// bool bNewerOnTop: �� �޽����� ���� �޽��� ���� ��ϵǰ� �� ���ΰ�.
		// int key: ������ Ű�� ����� ��� �� �޽����� ���� �޽����� ��ü�Ѵ�.
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("Item Message"));
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %f"), DeltaTime);

	if (GEngine)
	{
		FString message = FString::Printf(TEXT("DeltaTime: %f"), DeltaTime);
		FString name = GetName();
		FString nameMessage = FString::Printf(TEXT("DeltaTime: %s"), *name);

		// bool bNewerOnTop: �� �޽����� ���� �޽��� ���� ��ϵǰ� �� ���ΰ�.
		// int key: ������ Ű�� ����� ��� �� �޽����� ���� �޽����� ��ü�Ѵ�.
		GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Cyan, message);
		GEngine->AddOnScreenDebugMessage(3, 60.f, FColor::Cyan, nameMessage);
	
		UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *name);
	}
}

