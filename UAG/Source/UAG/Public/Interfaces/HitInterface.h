// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

// 인터페이스가 리플렉션에 참여할 수 있도록 하는 새로운 인터페이스.
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

// 다중 상속을 활용할 때 사용할 인터페이스.
// 함수를 선언하는 클래스.
class UAG_API IHitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 자식 클래스에서 무조건 재정의하도록 순수 가상 함수로 만든다.
	// const FVector&: 객체의 복사본을 만들지 않는다, 매개변수를 변경하지 않을 것이다.
	virtual void GetHit(const FVector& _impactPoint) = 0;
};
