// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayer.h"

#include "ChessRuleSubsystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChessPlayer::AChessPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	TimeToMove = 1.f;

	TimePassed = 0;

	bMoved = false;
	
	CameraComponent->SetRelativeLocation(ArrowComponentWhite->GetRelativeLocation());
	
	CameraComponent->SetRelativeRotation(ArrowComponentWhite->GetRelativeRotation());

	InitialPosition = CameraComponent->GetRelativeLocation();

	InitialRotation = CameraComponent->GetRelativeRotation();
	
	GetWorld()->GetSubsystem<UChessRuleSubsystem>()->ChessPlayer = this;
}

// Called every frame
void AChessPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimePassed += DeltaTime;

	if(bMoved)
	{
		if (TimePassed < TimeToMove)
		{
			FVector CurrentLocation = FMath::Lerp(InitialPosition, FinalPosition, FMath::Clamp(TimePassed/TimeToMove, 0.0f, 1.0f));
			FRotator CurrentRotation = FMath::Lerp(InitialRotation, FinalRotation, FMath::Clamp(TimePassed/TimeToMove, 0.0f, 1.0f));
			CameraComponent->SetRelativeLocation(CurrentLocation);
			CameraComponent->SetRelativeRotation(CurrentRotation);
		}
		else
		{
			InitialPosition = CameraComponent->GetRelativeLocation();
			InitialRotation = CameraComponent->GetRelativeRotation();
			bMoved = false;
		}
	}
}

// Called to bind functionality to input
void AChessPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChessPlayer::CameraWhite()
{
	FinalPosition = ArrowComponentWhite->GetRelativeLocation();
	FinalRotation = ArrowComponentWhite->GetRelativeRotation();

	bMoved = true;
	TimePassed = 0;

	UE_LOG(LogTemp, Warning, TEXT("White Camera"));
}

void AChessPlayer::CameraBlack()
{
	FinalPosition = ArrowComponentBlack->GetRelativeLocation();
	FinalRotation = ArrowComponentBlack->GetRelativeRotation();

	bMoved = true;
	TimePassed = 0;

	UE_LOG(LogTemp, Warning, TEXT("Black Camera"));
}

