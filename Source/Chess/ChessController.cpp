// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessController.h"

void AChessController::BeginPlay()
{
	Super::BeginPlay();
	
	ChessRuleSubsystem = GetWorld()->GetSubsystem<UChessRuleSubsystem>();
	
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
	
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, HitResult) && (!Piece || !Piece->GetMoved()))
	{
		if(HitResult.GetActor()->ActorHasTag(TEXT("Piece")))
		{
			TempPiece = HitResult.GetActor()->FindComponentByClass<UPieceMovementComponent>();
			if(ChessRuleSubsystem && ChessRuleSubsystem->GetTurn() == TempPiece->GetColour())
			{
				Piece = TempPiece;
				TempPiece = nullptr;
				Piece->Selected();
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

