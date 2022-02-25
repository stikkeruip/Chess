// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessController.h"

#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"


void AChessController::BeginPlay()
{
	Super::BeginPlay();
	
	ChessRuleSubsystem = GetWorld()->GetSubsystem<UChessRuleSubsystem>();
	
}

void AChessController::ClearSpawnedMovementIndicators()
{
	for (auto i : SpawnedActors)
	{
		i->Destroy();
	}
	SpawnedActors.Empty();
}

bool AChessController::IsValidMoveTarget(FVector HitLocation)
{
	for(auto i : SpawnedActors)
	{
		if(IsInSameGrid(HitLocation, i->GetActorLocation()))
		{
			return true;
		}
	}
	return false;
}

bool AChessController::IsInSameGrid(FVector CurrentPosition, FVector TargetPosition)
{
	if(abs(CurrentPosition.X - TargetPosition.X) < GRID_SIZE / 2 && abs(CurrentPosition.Y - TargetPosition.Y) < GRID_SIZE / 2)
	{
		return true;
	}
	return false;
}

void AChessController::DisplayMoves(FVector StartLocation, EPieceType PieceType, EColour PieceColour)
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	FRotator Rotation = FRotator();
	
	if (PieceType == EPieceType::PT_Castle)
	{
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			GetWorld()->LineTraceSingleByChannel(
				HitResult, StartLocation + FVector(XStraightOffset[DirectionIndex], YStraightOffset[DirectionIndex], 30.f),
				StartLocation + FVector(XStraightDir[DirectionIndex], YStraightDir[DirectionIndex], 30.f), ECC_Pawn, TraceParams);
			UE_LOG(LogTemp, Warning, TEXT("%i"), DirectionIndex);
			if (HitResult.GetActor() && HitResult.GetActor() != PieceBeingMoved)
			{
				FVector ActorHitPosition = HitResult.GetActor()->GetActorLocation();
				UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHitPosition.ToString());
				XYLimits.Add(ActorHitPosition);
				FVector DeltaVector = FVector(StepOffsetStraightX[DirectionIndex], StepOffsetStraightY[DirectionIndex], 0.0f);
				FVector FirstCheckPosition = StartLocation + DeltaVector;
				for (FVector CurrentPosition = FirstCheckPosition; !IsInSameGrid(CurrentPosition, ActorHitPosition); CurrentPosition += DeltaVector)
				{
					AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
					SpawnedActors.Add(SpawnedActor);
				}
			}
		}
	}
	if (PieceType == EPieceType::PT_Bishop)
	{
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			GetWorld()->LineTraceSingleByChannel(
				HitResult, StartLocation + FVector(XDiagonalOffset[DirectionIndex], YDiagonalOffset[DirectionIndex], 30.f),
				StartLocation + FVector(XDiagonalDir[DirectionIndex], YDiagonalDir[DirectionIndex], 30.f), ECC_Pawn, TraceParams);
			if (HitResult.GetActor() && HitResult.GetActor() != PieceBeingMoved)
			{
				FVector TargetPosition = HitResult.GetActor()->GetActorLocation();
				FVector DeltaVector = FVector(StepOffsetDiagonalX[DirectionIndex], StepOffsetDiagonalY[DirectionIndex], 0.0f);
				FVector FirstCheckPosition = StartLocation + DeltaVector;
				for (FVector CurrentPosition = FirstCheckPosition; !IsInSameGrid(CurrentPosition, TargetPosition); CurrentPosition += DeltaVector)
				{
					AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
					SpawnedActors.Add(SpawnedActor);
				}
			}
		}
	}
	if (PieceType == EPieceType::PT_Queen)
	{
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			GetWorld()->LineTraceSingleByChannel(
				HitResult, StartLocation + FVector(XDiagonalOffset[DirectionIndex], YDiagonalOffset[DirectionIndex], 30.f),
				StartLocation + FVector(XDiagonalDir[DirectionIndex], YDiagonalDir[DirectionIndex], 30.f), ECC_Pawn, TraceParams);
			if (HitResult.GetActor() && HitResult.GetActor() != PieceBeingMoved)
			{
				FVector TargetPosition = HitResult.GetActor()->GetActorLocation();
				FVector DeltaVector = FVector(StepOffsetDiagonalX[DirectionIndex], StepOffsetDiagonalY[DirectionIndex], 0.0f);
				FVector FirstCheckPosition = StartLocation + DeltaVector;
				for (FVector CurrentPosition = FirstCheckPosition; !IsInSameGrid(CurrentPosition, TargetPosition); CurrentPosition += DeltaVector)
				{
					AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
					SpawnedActors.Add(SpawnedActor);
				}
			}
		}
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			GetWorld()->LineTraceSingleByChannel(
				HitResult, StartLocation + FVector(XStraightOffset[DirectionIndex], YStraightOffset[DirectionIndex], 20.f),
				StartLocation + FVector(XStraightDir[DirectionIndex], YStraightDir[DirectionIndex], 20.f), ECC_Pawn, TraceParams);
			if (HitResult.GetActor() && HitResult.GetActor() != PieceBeingMoved)
			{
				FVector TargetPosition = HitResult.GetActor()->GetActorLocation();
				FVector DeltaVector = FVector(StepOffsetStraightX[DirectionIndex], StepOffsetStraightY[DirectionIndex], 0.0f);
				FVector FirstCheckPosition = StartLocation + DeltaVector;
				for (FVector CurrentPosition = FirstCheckPosition; !IsInSameGrid(CurrentPosition, TargetPosition); CurrentPosition += DeltaVector)
				{
					AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
					SpawnedActors.Add(SpawnedActor);
				}
			}
		}
	}
	if (PieceType == EPieceType::PT_King)
	{
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			FVector CurrentPosition = StartLocation + FVector(XKingDirStraight[DirectionIndex], YKingDirStraight[DirectionIndex], 0.f);
			AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
			SpawnedActors.Add(SpawnedActor);
		}
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			FVector CurrentPosition = StartLocation + FVector(XKingDirDiagonal[DirectionIndex], YKingDirDiagonal[DirectionIndex], 0.f);
			AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
			SpawnedActors.Add(SpawnedActor);
		}
	}
	if (PieceType == EPieceType::PT_Knight)
	{
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			FVector CurrentPosition = StartLocation + FVector(XKnightDir[DirectionIndex], YKnightDir[DirectionIndex], 0.f);
			AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
			SpawnedActors.Add(SpawnedActor);
		}
		for (int DirectionIndex = 0; DirectionIndex < DirectionNum; DirectionIndex++)
		{
			FVector CurrentPosition = StartLocation + FVector(YKnightDir[DirectionIndex], XKnightDir[DirectionIndex], 0.f);
			AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &CurrentPosition, &Rotation);
			SpawnedActors.Add(SpawnedActor);
		}
	}
	if (PieceType == EPieceType::PT_Pawn)
	{
		float MoveDirection;
		float MoveDistance;

		MoveDistance = Piece->GetFirstMove() ? 200.f : 100.f;

		MoveDirection = PieceColour == EColour::C_White ? 1 : -1;
		
		for(int i = 100; i <= MoveDistance; i+= 100)
		{
			GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation + FVector(0.f, MoveDirection * 60.f, 20.f), StartLocation + FVector(0.f, MoveDistance * MoveDirection, 20.f), ECC_Pawn, TraceParams);
			if (!HitResult.GetActor() && HitResult.GetActor() != PieceBeingMoved)
			{
				FVector SpawnPosition = StartLocation + FVector(0.f, i * MoveDirection, 20.f);
				AActor* SpawnedActor = GetWorld()->SpawnActor(ActorToSpawn, &SpawnPosition, &Rotation);
				SpawnedActors.Add(SpawnedActor);
			}
		}
	}
	ChessRuleSubsystem->SetYLimitMax(XYLimits[0].Y); 
	ChessRuleSubsystem->SetYLimitMin(XYLimits[1].Y); 
	ChessRuleSubsystem->SetXLimitMin(XYLimits[2].X); 
	ChessRuleSubsystem->SetXLimitMax(XYLimits[3].X); 
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
	FCollisionQueryParams TraceParams;
	
	if (GetHitResultUnderCursor(ECC_Pawn, true, HitResult) && (!Piece || !Piece->GetMoved()))
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
					PieceBeingMoved = HitResult.GetActor();
					TempPiece = nullptr;
					Piece->Selected();
				
					DisplayMoves(HitLocation, Piece->GetPieceType(), Piece->GetColour());
				
					return;
				}
			}
			FVector HitLocation = HitActor->GetActorLocation();

			if(Piece && !TempPiece)
			{
				if(Piece->SetEndPosition(HitLocation) && IsValidMoveTarget(HitLocation))
				{
					ClearSpawnedMovementIndicators();
					Piece->SetMoved();
				}
			}
			if(Piece && TempPiece)
			{
				if(Piece->SetEndPosition(HitLocation))
				{
					ClearSpawnedMovementIndicators();
					Piece->Attack(TempPiece);
				}
			}
		}
	}
}

