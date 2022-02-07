// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceMovementComponent.h"

// Sets default values for this component's properties
UPieceMovementComponent::UPieceMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PieceState = EPieceState::PS_Unselected;
	Piece = Cast<APiece>(GetOwner());
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

	bAttacked = false;

	bAttacking = false;

	ChessRuleSubsystem = GetWorld()->GetSubsystem<UChessRuleSubsystem>();
	if(ChessRuleSubsystem)
	{
		PieceStateChange.AddUObject(ChessRuleSubsystem, &UChessRuleSubsystem::InstructionCompleted);
		ChessRuleSubsystem->AddPiece(this);
	}
}


// Called every frame
void UPieceMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TimePassed += DeltaTime;
	
	if(bMoved)
	{
		if (bAttacked && CanAttack())
		{
			bMoved = false;
			bAttacking = true;
		}
		if (TimePassed < TimeToMove)
		{
			FVector CurrentLocation = FMath::Lerp(InitialPosition, EndPosition, FMath::Clamp(TimePassed/TimeToMove, 0.0f, 1.0f));
			GetOwner()->SetActorLocation(CurrentLocation);
		}
		else
		{
			InitialPosition = GetOwner()->GetActorLocation();
			bMoved = false;
			PieceState = EPieceState::PS_Unselected;
			PieceStateChange.Broadcast(Colour, PieceState);
			ChessRuleSubsystem->EndTurn(Colour);
		}
	}
}

bool UPieceMovementComponent::CanAttack()
{
	return (FVector::DistXY(GetGridPosition(), EndPosition) < 150);
}

bool UPieceMovementComponent::SetEndPosition(FVector Pos)
{
	if(ChessRuleSubsystem->CheckMovementValid(Piece_Type, Colour, Pos.X, Pos.Y, GetGridPosition()))
	{
		EndPosition = Pos;
		return true;
	}
	return false;
}

void UPieceMovementComponent::SetMoved()
{
	PieceState = EPieceState::PS_Moving;
	PieceStateChange.Broadcast(Colour, PieceState);
	
	bMoved = true;
	TimePassed = 0;
}

void UPieceMovementComponent::Attack(UPieceMovementComponent* PieceMovementComponent, AActor* Actor)
{
	ChessRuleSubsystem->RemovePiece(PieceMovementComponent);

	bAttacked = true;
	SetMoved();
}


void UPieceMovementComponent::Selected()
{
	PieceState = EPieceState::PS_Selected;
	PieceStateChange.Broadcast(Colour, PieceState);
}

FVector UPieceMovementComponent::GetGridPosition()
{
	return GetOwner()->GetActorLocation();
}

void UPieceMovementComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *PropertyChangedEvent.GetPropertyName().ToString());

	if(PropertyChangedEvent.GetPropertyName().ToString().Compare("Colour") == 0)
	{
		Piece->ChangeMaterial(Colour, Piece_Type);
	}
	if(PropertyChangedEvent.GetPropertyName().ToString().Compare("Piece_Type") == 0)
	{
		Piece->ChangeMesh(Piece_Type);
	}
}






