// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessController.h"
#include "ChessRuleSubsystem.h"



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
	
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, HitResult) && (Piece == nullptr || !Piece->GetMoving()))
	{
		if(HitResult.GetActor()->ActorHasTag(TEXT("Piece")))
		{
			Piece = HitResult.GetActor()->FindComponentByClass<UPieceMovementComponent>();
			Piece->Selected();
			return;
		}
		FVector HitLocation = HitResult.GetActor()->GetActorLocation();

		UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString())

		if(Piece != nullptr)
		{
			Piece->SetEndPosition(HitLocation);
			Piece->Moved();
		}
	}
}

