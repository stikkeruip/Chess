// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessController.h"
#include "DrawDebugHelpers.h"


void AChessController::BeginPlay()
{
	Super::BeginPlay();
	
	ChessRuleSubsystem = GetWorld()->GetSubsystem<UChessRuleSubsystem>();
	
}

void AChessController::DisplayMoves(FVector StartLocation, EPieceType PieceType, EColour PieceColour)
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	FRotator Rotation = FRotator();
	FVector ActorSpawnLocation;
	
	if (PieceType == EPieceType::PT_Castle)
	{
		for (int y = 0; y <= 3; y++)
		{
			GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation + FVector(XStartOffset[y], YStartOffset[y], 20.f), StartLocation + FVector(XDir[y], YDir[y], 20.f), ECC_Pawn, TraceParams);
			if(HitResult.GetActor())
			{
				for(int i = round(PiecePos(StartLocation, y) + HitDir[y]); i > round(PiecePos(HitResult.GetActor()->GetActorLocation(), y)); i += HitDir[y])
				{
					if(y <= 1 )
					{
						ActorSpawnLocation = FVector(round(StartLocation.X), i, 30.f);
						
						GetWorld()->SpawnActor(ActorToSpawn, &ActorSpawnLocation, &Rotation);
					}
					else
					{
						ActorSpawnLocation = FVector(i, round(ActorSpawnLocation.Y), 30.f);
						
						GetWorld()->SpawnActor(ActorToSpawn, &ActorSpawnLocation, &Rotation);
					}
					
				}
				for(int i = round(PiecePos(StartLocation, y) + HitDir[y]); i < round(PiecePos(HitResult.GetActor()->GetActorLocation(), y)); i += HitDir[y])
				{
					if(y <= 1 )
					{
						ActorSpawnLocation = FVector(round(StartLocation.X), i, 30.f);
						
						GetWorld()->SpawnActor(ActorToSpawn, &ActorSpawnLocation, &Rotation);
					}
					else
					{
						ActorSpawnLocation = FVector(i, round(ActorSpawnLocation.Y), 30.f);
						
						GetWorld()->SpawnActor(ActorToSpawn, &ActorSpawnLocation, &Rotation);
					}
				}
			}
		}
	}
}

float AChessController::PiecePos(FVector PPiece, int Pos)
{
	if(Pos == 0 || Pos == 1)
	{
		return PPiece.Y;
	}
	return PPiece.X;
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
		if(HitResult.GetActor()->ActorHasTag(TEXT("Piece")))
		{
			TempPiece = HitResult.GetActor()->FindComponentByClass<UPieceMovementComponent>();
			if(ChessRuleSubsystem && ChessRuleSubsystem->GetTurn() == TempPiece->GetColour())
			{
				FVector HitLocation = HitResult.GetActor()->GetActorLocation();
				
				Piece = TempPiece;
				TempPiece = nullptr;
				Piece->Selected();
				
				DisplayMoves(HitLocation, Piece->GetPieceType(), Piece->GetColour());
				
				return;
			}
		}
		FVector HitLocation = HitResult.GetActor()->GetActorLocation();

		if(Piece && !TempPiece)
		{
			if(Piece->SetEndPosition(HitLocation))
				Piece->SetMoved();
		}
		if(Piece && TempPiece)
		{
			if(Piece->SetEndPosition(HitLocation))
				Piece->Attack(TempPiece, HitResult.GetActor());
		}
	}
}

