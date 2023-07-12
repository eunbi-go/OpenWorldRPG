// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"
#include "Characters/AGCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Interfaces/HitInterface.h"

AWeapon::AWeapon()
{
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	boxComp->SetupAttachment(GetRootComponent());
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	boxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	boxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	boxTraceStart->SetupAttachment(GetRootComponent());
	boxTraceStart->SetRelativeLocation(FVector(0.f, 0.f, -30.f));

	boxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	boxTraceEnd->SetupAttachment(GetRootComponent());
	boxTraceEnd->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}

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

	// ���� ���Ŀ��� sphereComp �� ���� ������ �̺�Ʈ �߻� X.
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

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// GetComponentLocation(): ���� ���������� ��ġ ��ȯ.
	const FVector start = boxTraceStart->GetComponentLocation();
	const FVector end = boxTraceEnd->GetComponentLocation();

	TArray<AActor*> actorsToIgnoreArray;
	actorsToIgnoreArray.Add(this);

	// �� ���� �� ���͸� 2�� �̻� hit ���� �ʵ���.
	// ignoreActors �迭�� ���� ��Ÿ�ְ� ���� �� �ʱ�ȭ.
	for (AActor* actor : ignoreActors)
		actorsToIgnoreArray.AddUnique(actor);

	FHitResult boxHit;

	UKismetSystemLibrary::BoxTraceSingle(
		this, start, end, FVector(5.f),
		boxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		actorsToIgnoreArray,	// �������� ������ ���͵��� �迭
		EDrawDebugTrace::None,	// None: ����� �ڽ��� ���� �ʰڴ�, ForDuration: �� �� ���� ���ڴ�.
		boxHit,
		true	// �ڱ� �ڽ��� �����Ѵ�.
	);

	// �浹�� ��ü�� IHitInterface �� ��ӹ޾��� ���, �ش� Ŭ������ GetHit() �Լ� ȣ��.
	if (boxHit.GetActor())
	{
		IHitInterface* hitInterface = Cast<IHitInterface>(boxHit.GetActor());
		if (hitInterface)
		{
			hitInterface->GetHit(boxHit.ImpactPoint);

			// BP ���� ȣ��.
			//hitInterface->Execute_GetHit(boxHit.GetActor(), boxHit.ImpactPoint);
		}

		// AddUnique(): ignoreActors �迭�� �������� ���Ͱ� �̹� �����ϴ��� Ȯ��.
		ignoreActors.AddUnique(boxHit.GetActor());

		CreateFields(boxHit.ImpactPoint);
	}
}