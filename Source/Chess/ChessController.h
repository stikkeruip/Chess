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

	UChessRuleSubsystem* ChessRuleSubsystem;
	
	FVector DesiredPosition;

	virtual void SetupInputComponent() override;

	void OnMouseClick();

	APawn* Player;

	UPieceMovementComponent* Piece;
	
	UPieceMovementComponent* TempPiece;

	float XDir[4] = {0.f, 0.f, 800.f, -800.f};
	float YDir[4] = {800.f, -800.f, 0.f, 0.f};
	float XStartOffset [4] = {0.f, 0.f, 60.f, -60.f};
	float YStartOffset [4] = {60.f, -60.f, 0.f, 0.f};
	int HitDir[4] = {100, -100, 100, -100}; 
	
	float PiecePos(FVector PPiece, int Pos);
	
public:

	virtual void BeginPlay() override;

	void DisplayMoves(FVector Start, EPieceType PieceType, EColour PieceColour);
};
