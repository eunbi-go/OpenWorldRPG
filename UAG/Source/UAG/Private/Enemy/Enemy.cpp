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
	// GetSafeNormal(): ������ ����ȭ�� ������ ����ȭ���� Ȯ��.
	const FVector hitDirection = (impactLowered - GetActorLocation()).GetSafeNormal();

	// �����Ͽ� cos(theta) ���� ��´�.
	const double cosTheta = FVector::DotProduct(forward, hitDirection);
	// cos �� ���ﰢ�Լ��� Ȱ���Ͽ� ���� ������ ��´�.
	double theta = FMath::Acos(cosTheta);
	// �𸮾� �ﰢ�Լ��� �� ��� ������ ����ϹǷ� ���ȿ��� ������ ��ȯ�Ѵ�.
	theta = FMath::RadiansToDegrees(theta);

	// corssProduct �� ���� ����Ű�� �����ʿ��� �°� �ִٴ� ���� �ǹ��Ѵ�.
	// �Ʒ����� ���ϰ� �ִٸ� ������ ������ �����̱� ������ ���ʿ��� ���ݹް� �ִٴ� ���� �ǹ��Ѵ�.
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
