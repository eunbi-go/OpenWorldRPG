// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Capsule: 언리얼 엔진 내부에서 사용할 이름 설정.
	capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(capsule);


	birdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	birdMesh->SetupAttachment(GetRootComponent());

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->TargetArmLength = 300.f;

	viewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	viewCamera->SetupAttachment(cameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(birdMappingContext, 0);
		}
	}
}

void ABird::Move(const FInputActionValue& _value)
{
	const float directionValue = _value.Get<float>();

	if (GetController() && (directionValue != 0.f))
	{
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, directionValue);
	}
}

void ABird::Look(const FInputActionValue& _value)
{
	const FVector2D lookAxisValue = _value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(lookAxisValue.X);
		AddControllerPitchInput(lookAxisValue.Y);
	}
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 축 매핑에서 바인딩하는 데 사용하는 함수: 콜백 함수.
	// &ABird::MoveForward: 함수의 주소를 입력 매개변수로 다른 함수에 전달.
	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &ABird::Look);
	}
}

