// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class UAG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine params")
		float	amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine params")
		float	timeConstant = 5.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

	template<typename T>
	T Avg(T first, T second);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float	runningTime = 0.f;

	// UPROPERTY(): ������ �÷��ǿ� ����.
	// VisibleAnywhere: static mesh �� �����ϱ� ���� �ش� �����͸� �������Ʈ �����Ϳ� �����Ŵ.
	UPROPERTY(VisibleAnywhere)
	// ������Ʈ�� ���� ������ ����.
	UStaticMeshComponent* itemMesh;
};

template<typename T>
inline T AItem::Avg(T first, T second)
{
	return (first + second) / 2;
}
