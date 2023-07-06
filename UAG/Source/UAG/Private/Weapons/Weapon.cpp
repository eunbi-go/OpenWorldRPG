// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"
#include "Characters/AGCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

void AWeapon::Equip(USceneComponent* _parent, FName _socketName)
{
	AttachMeshToSocket(_parent, _socketName);
	itemState = EItemState::EIS_Equip;
	if (equipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, equipSound, GetActorLocation()
		);
	}

	// 장착 이후에는 sphereComp 에 의한 오버랩 이벤트 발생 X.
	if (sphereComp)
	{
		sphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::AttachMeshToSocket(USceneComponent* _parent, const FName& _socketName)
{
	FAttachmentTransformRules transformRules(EAttachmentRule::SnapToTarget, true);
	itemMesh->AttachToComponent(_parent, transformRules, _socketName);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
