// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayer.h"

#include "ChessRuleSubsystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChessPlayer::AChessPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	ArrowComponentWhite = CreateDefaultSubobject<UArrowComponent>(TEXT("WhiteArrow"));
	ArrowComponentBlack = CreateDefaultSubobject<UArrowComponent>(TEXT("BlackArrow"));

	CameraComponent->SetupAttachment(RootComponent);
	ArrowComponentBlack->SetupAttachment(RootComponent);
	ArrowComponentWhite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AChessPlayer::BeginPlay()
{
	Super::BeginPlay();

	CameraWhite();
	
	GetWorld()->GetSubsystem<UChessRuleSubsystem>()->ChessPlayer = this;
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

	UE_LOG(LogTemp, Warning, TEXT("White Camera"));
}

void AChessPlayer::CameraBlack()
{
	CameraComponent->SetRelativeLocation(ArrowComponentBlack->GetRelativeLocation());
	CameraComponent->SetRelativeRotation(ArrowComponentBlack->GetRelativeRotation());

	UE_LOG(LogTemp, Warning, TEXT("Black Camera"));
}

