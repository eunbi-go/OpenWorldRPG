// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraComponent;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equip
};

UCLASS()
class UAG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	// 진폭
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

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// UPROPERTY(): 가비지 컬렉션에 참여.
	// VisibleAnywhere: static mesh 를 변경하기 위해 해당 포인터를 블루프린트 에디터에 노출시킴.
	UPROPERTY(VisibleAnywhere)
	// 컴포넌트에 대한 포인터 생성.
	UStaticMeshComponent* itemMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* sphereComp;

	EItemState itemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* niagaraComp;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float	runningTime = 0.f;

	
};

template<typename T>
inline T AItem::Avg(T first, T second)
{
	return (first + second) / 2;
}
