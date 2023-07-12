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

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// GetComponentLocation(): 월드 공간에서의 위치 반환.
	const FVector start = boxTraceStart->GetComponentLocation();
	const FVector end = boxTraceEnd->GetComponentLocation();

	TArray<AActor*> actorsToIgnoreArray;
	actorsToIgnoreArray.Add(this);

	// 한 번에 한 액터를 2번 이상 hit 하지 않도록.
	// ignoreActors 배열은 공격 몽타주가 끝날 때 초기화.
	for (AActor* actor : ignoreActors)
		actorsToIgnoreArray.AddUnique(actor);

	FHitResult boxHit;

	UKismetSystemLibrary::BoxTraceSingle(
		this, start, end, FVector(5.f),
		boxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		actorsToIgnoreArray,	// 추적에서 무시할 액터들의 배열
		EDrawDebugTrace::None,	// None: 디버깅 박스를 보지 않겠다, ForDuration: 몇 초 동안 보겠다.
		boxHit,
		true	// 자기 자신은 무시한다.
	);

	// 충돌한 객체가 IHitInterface 를 상속받았을 경우, 해당 클래스의 GetHit() 함수 호출.
	if (boxHit.GetActor())
	{
		IHitInterface* hitInterface = Cast<IHitInterface>(boxHit.GetActor());
		if (hitInterface)
		{
			hitInterface->GetHit(boxHit.ImpactPoint);

			// BP 버전 호출.
			//hitInterface->Execute_GetHit(boxHit.GetActor(), boxHit.ImpactPoint);
		}

		// AddUnique(): ignoreActors 배열에 넣으려는 액터가 이미 존재하는지 확인.
		ignoreActors.AddUnique(boxHit.GetActor());

		CreateFields(boxHit.ImpactPoint);
	}
}