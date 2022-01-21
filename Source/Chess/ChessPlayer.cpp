// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayer.h"

// Sets default values
AChessPlayer::AChessPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	ArrowComponentWhite = CreateDefaultSubobject<UArrowComponent>(TEXT("WhiteArrow"));
	ArrowComponentBlack = CreateDefaultSubobject<UArrowComponent>(TEXT("BlackArrow"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AChessPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChessPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChessPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChessPlayer::CameraWhite()
{
	CameraComponent->SetRelativeLocation(ArrowComponentWhite->GetRelativeLocation());
	CameraComponent->SetRelativeRotation(ArrowComponentWhite->GetRelativeRotation());
}

void AChessPlayer::CameraBlack()
{
	CameraComponent->SetRelativeLocation(ArrowComponentBlack->GetRelativeLocation());
	CameraComponent->SetRelativeRotation(ArrowComponentBlack->GetRelativeRotation());
}

