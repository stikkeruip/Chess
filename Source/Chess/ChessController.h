// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PieceMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChessController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessController : public APlayerController
{
	GENERATED_BODY()


	FVector DesiredPosition;

	virtual void SetupInputComponent() override;

	void OnMouseClick();

	APawn* Player;
	
public:
	UPieceMovementComponent* Piece;
};
