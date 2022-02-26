// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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

	bMoving = false;

	bGoingToAttack = false;

	bAttacking = false;

	bFirstMove = true;

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
	
	if(bMoving && !bAttacking)
	{
		if (bGoingToAttack && CanAttack())
		{
			bGoingToAttack = false;
			bAttacking = true;
			bMoving = false;
		}
		else
		{
			TimePassed += DeltaTime;
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
				PieceStateChange.Broadcast();
				ChessRuleSubsystem->EndTurn(Colour);
			}
		}
	}
}

void UPieceMovementComponent::DestroyAttackedActor()
{
	AttackedActor->Destroy();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyedParticleSystem, AttackedActor->GetActorLocation());
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
	PieceStateChange.Broadcast();
	
	bMoving = true;
	bFirstMove = false;
	TimePassed = 0;
}

void UPieceMovementComponent::Attack(UPieceMovementComponent* PieceMovementComponent)
{
	AttackedActor = PieceMovementComponent->GetOwner();
	ChessRuleSubsystem->RemovePiece(PieceMovementComponent);

	bGoingToAttack = true;
	SetMoved();
}


void UPieceMovementComponent::Selected()
{
	PieceState = EPieceState::PS_Selected;
	PieceStateChange.Broadcast();
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






