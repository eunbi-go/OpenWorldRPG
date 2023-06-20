// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	// LogTemp: 디버깅 목적으로 자주 추가/제거되는 로그에 사용된다.
	// Warning: 다양한 로그 범주 중 하나.
	UE_LOG(LogTemp, Warning, TEXT("Begin Play called"));

	if (GEngine)
	{
		// bool bNewerOnTop: 새 메시지가 이전 메시지 위에 기록되게 할 것인가.
		// int key: 동일한 키를 사용할 경우 새 메시지가 이전 메시지를 대체한다.
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

		// bool bNewerOnTop: 새 메시지가 이전 메시지 위에 기록되게 할 것인가.
		// int key: 동일한 키를 사용할 경우 새 메시지가 이전 메시지를 대체한다.
		GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Cyan, message);
		GEngine->AddOnScreenDebugMessage(3, 60.f, FColor::Cyan, nameMessage);
	
		UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *name);
	}
}

