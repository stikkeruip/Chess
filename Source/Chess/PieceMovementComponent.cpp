// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceMovementComponent.h"

// Sets default values for this component's properties
UPieceMovementComponent::UPieceMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPieceMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	TimeToMove = 2.f;

	TimePassed = 0;

	InitialPosition = GetOwner()->GetActorLocation();

	bMoved = false;

	bMoving = false;
	// ...
	
}


// Called every frame
void UPieceMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimePassed += DeltaTime;
	
	if(bMoved)
	{
		bMoving = true;
		if (TimePassed < TimeToMove)
		{
			FVector CurrentLocation = FMath::Lerp(InitialPosition, EndPosition, FMath::Clamp(TimePassed/TimeToMove, 0.0f, 1.0f));

			GetOwner()->SetActorLocation(CurrentLocation);
		}
		else
		{
			InitialPosition = GetOwner()->GetActorLocation();
			bMoving = false;
		}
	}
}

void UPieceMovementComponent::SetEndPosition(FVector Pos)
{
	EndPosition = Pos;
}

void UPieceMovementComponent::Moved()
{
	bMoved = true;
	TimePassed = 0;
}




