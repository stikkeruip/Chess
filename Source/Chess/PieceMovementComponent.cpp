// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceMovementComponent.h"

#include "ChessRuleSubsystem.h"

// Sets default values for this component's properties
UPieceMovementComponent::UPieceMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Colour = EColour::C_None;
	PieceState = EPieceState::PS_Unselected;

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

	UChessRuleSubsystem* ChessRuleSubsystem = GetWorld()->GetSubsystem<UChessRuleSubsystem>();
	if(ChessRuleSubsystem)
	{
		PieceStateChange.AddUObject(ChessRuleSubsystem, &UChessRuleSubsystem::InstructionCompleted);
	}
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
			PieceState = EPieceState::PS_Unselected;
			PieceStateChange.Broadcast(Colour, PieceState);
		}
	}
}

void UPieceMovementComponent::SetEndPosition(FVector Pos)
{
	EndPosition = Pos;
}

void UPieceMovementComponent::Moved()
{
	PieceState = EPieceState::PS_Moving;
	PieceStateChange.Broadcast(Colour, PieceState);
	
	bMoved = true;
	TimePassed = 0;
}

void UPieceMovementComponent::Selected()
{
	PieceState = EPieceState::PS_Selected;
	PieceStateChange.Broadcast(Colour, PieceState);
}




