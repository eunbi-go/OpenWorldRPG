// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "UAG/DebugMacros.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::PlayHitMontages(const FName& _sectionName)
{
	UAnimInstance* animInst = GetMesh()->GetAnimInstance();
	if (animInst && hitMontage)
	{
		animInst->Montage_Play(hitMontage);
		animInst->Montage_JumpToSection(_sectionName, hitMontage);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit(const FVector& _impactPoint)
{
	//DRAW_SPHERE_COLOR(_impactPoint, FColor::Orange);
	
	CalculateHitDegree(_impactPoint);

	if (hitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			hitSound,
			_impactPoint
		);
	}

	if (hitParticle && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			hitParticle,
			_impactPoint
		);
	}
}

void AEnemy::CalculateHitDegree(const FVector& _impactPoint)
{
	const FVector forward = GetActorForwardVector();
	const FVector impactLowered(_impactPoint.X, _impactPoint.Y, GetActorLocation().Z);
	// GetSafeNormal(): 벡터의 정규화가 안전한 정규화인지 확인.
	const FVector hitDirection = (impactLowered - GetActorLocation()).GetSafeNormal();

	// 내적하여 cos(theta) 값을 얻는다.
	const double cosTheta = FVector::DotProduct(forward, hitDirection);
	// cos 의 역삼각함수를 활용하여 실제 각도를 얻는다.
	double theta = FMath::Acos(cosTheta);
	// 언리얼 삼각함수는 도 대신 라디안을 사용하므로 라디안에서 각도로 변환한다.
	theta = FMath::RadiansToDegrees(theta);

	// corssProduct 가 위를 가리키면 오른쪽에서 맞고 있다는 것을 의미한다.
	// 아래쪽을 향하고 있다면 공격이 전방의 왼쪽이기 때문에 왼쪽에서 공격받고 있다는 것을 의미한다.
	const FVector crossProduct = FVector::CrossProduct(forward, hitDirection);
	if (crossProduct.Z < 0)
	{
		theta *= -1.f;
	}

	FName sectionName = FName("HitBack");

	if (theta >= -45.f && theta < 45.f)
		sectionName = FName("HitFront");
	else if (theta >= -135.f && theta < -45.f)
		sectionName = FName("HitLeft");
	else if (theta >= 45.f && theta < 135.f)
		sectionName = FName("HitRight");

	PlayHitMontages(sectionName);

	/*UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + crossProduct * 100.f, 5.f, FColor::Blue, 5.f);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Theta : %f"), theta));
	}
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + forward * 60.f, 5.f, FColor::Red, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + hitDirection * 60.f, 5.f, FColor::Green, 5.f);*/
}
