// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessController.h"
#include "DrawDebugHelpers.h"


void AChessController::BeginPlay()
{
	Super::BeginPlay();
	
	ChessRuleSubsystem = GetWorld()->GetSubsystem<UChessRuleSubsystem>();
	
}

bool AChessController::IsInSameGrid(FVector CurrentPosition, FVector TargetPosition)
{
	if(abs(CurrentPosition.X - TargetPosition.X) < GRID_SIZE / 2 && abs(CurrentPosition.Y - TargetPosition.Y) < GRID_SIZE / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AChessController::DisplayMoves(FVector StartLocation, EPieceType PieceType, EColour PieceColour)
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	FRotator Rotation = FRotator();
	FVector ActorSpawnLocation;
	
	if (PieceType == EPieceType::PT_Castle)
	{
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			GetWorld()->LineTraceSingleByChannel(
				HitResult, StartLocation + FVector(XStartOffset[DirectionIndex], YStartOffset[DirectionIndex], 20.f),
				StartLocation + FVector(XDir[DirectionIndex], YDir[DirectionIndex], 20.f), ECC_Pawn, TraceParams);
			if (HitResult.GetActor())
			{
				FVector TargetPosition = HitResult.GetActor()->GetActorLocation();
				FVector DeltaVector = FVector(StepOffsetX[DirectionIndex], StepOffsetY[DirectionIndex], 0.0f);
				FVector FirstCheckPosition = StartLocation + DeltaVector;
				for (FVector CurrentPosition = FirstCheckPosition; !IsInSameGrid(CurrentPosition, TargetPosition); CurrentPosition += DeltaVector)
				{
					GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
				}
			}
		}
	}
}

float AChessController::PositionOnDirection(FVector Vector, int DirectionIndex)
{
	if(DirectionIndex == DirectionUp || DirectionIndex == DirectionDown)
	{
		return Vector.Y;
	}
	else
	{
		return Vector.X;
	}
}

void AChessController::SetupInputComponent()
{
	Super::SetupInputComponent();

	bEnableClickEvents = true;

	bShowMouseCursor = true;

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &AChessController::OnMouseClick);

	Piece = nullptr;
}

void AChessController::OnMouseClick()
{
	FHitResult HitResult;
	FHitResult Start;
	FCollisionQueryParams TraceParams;
	
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, HitResult) && (!Piece || !Piece->GetMoved()))
	{
		if(HitResult.GetActor())
		{
			AActor* HitActor = HitResult.GetActor();
			if(HitActor->ActorHasTag(TEXT("Piece")))
			{
				TempPiece = HitActor->FindComponentByClass<UPieceMovementComponent>();
				if(ChessRuleSubsystem && ChessRuleSubsystem->GetTurn() == TempPiece->GetColour())
				{
					FVector HitLocation = HitActor->GetActorLocation();
				
					Piece = TempPiece;
					TempPiece = nullptr;
					Piece->Selected();
				
					DisplayMoves(HitLocation, Piece->GetPieceType(), Piece->GetColour());
				
					return;
				}
			}
			FVector HitLocation = HitActor->GetActorLocation();

			if(Piece && !TempPiece)
			{
				if(Piece->SetEndPosition(HitLocation))
					Piece->SetMoved();
			}
			if(Piece && TempPiece)
			{
				if(Piece->SetEndPosition(HitLocation))
					Piece->Attack(TempPiece, HitActor);
			}
		}
	}
}

