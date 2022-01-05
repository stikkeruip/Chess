// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceMovementComponent.h"

#include "ChessRuleSubsystem.h"

// Sets default values for this component's properties
UPieceMovementComponent::UPieceMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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
			//PieceStateChange.Broadcast(Colour, PieceState);
		}
	}
}

bool UPieceMovementComponent::SetEndPosition(FVector Pos)
{
	EndPosition = Pos;

	return CheckMovementValid(Piece_Type, Pos.X, Pos.Y);
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

FVector UPieceMovementComponent::GetGridPosition(FVector Pos)
{
	return GetOwner()->GetActorLocation();
}

bool UPieceMovementComponent::CheckMovementValid(EPieceType PieceType, float F_X, float F_Y)
{
	CurrentGrid = GetGridPosition(InitialPosition);
	
	CurrentGridX = round(abs(CurrentGrid.X)/100);
	CurrentGridY = round(abs(CurrentGrid.Y)/100);
	
	F_X = round(abs(F_X)/100);
	F_Y = round(abs(F_Y)/100);
	
	if (PieceType == EPieceType::PT_Pawn && F_X == CurrentGridX && F_Y == (CurrentGridY + 1))
	{
		return true;
	}
	if (PieceType == EPieceType::PT_Castle && (F_X >= 1 && F_X <= 8 && F_Y == CurrentGridY || F_Y >= 1 && F_Y <= 8 && F_X == CurrentGridX))
	{
		return true;
	}

	return false;
}





