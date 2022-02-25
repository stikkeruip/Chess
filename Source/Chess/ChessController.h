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

	virtual void SetupInputComponent() override;

	void OnMouseClick();

	AActor* PieceBeingMoved;
	
	UPieceMovementComponent* Piece;
	
	UPieceMovementComponent* TempPiece;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ActorToSpawn;

	
	enum Direction
	{
		DirectionUp,
		DirectionDown,
		DirectionRight,
		DirectionLeft,
		DirectionNum
	};
	const int GRID_SIZE = 100;
	
	float XStraightDir[4] = {0.f, 0.f, 800.f, -800.f};
	float YStraightDir[4] = {800.f, -800.f, 0.f, 0.f};
	
	float XDiagonalDir[4] = {800.f, 800.f, -800.f, -800.f};
	float YDiagonalDir[4] = {800.f, -800.f, 800.f, -800.f};

	float XKnightDir [4] = {-100.f, 100.f, -100.f, 100.f};
	float YKnightDir [4] = {200.f, 200.f, -200.f, -200.f};

	float XKingDirDiagonal[4] = {-100.f, 100.f, -100.f, 100.f};
	float YKingDirDiagonal[4] = {100.f, 100.f, -100.f, -100.f};
	float XKingDirStraight[4] = {0.f, 0.f, -100.f, 100};
	float YKingDirStraight[4] = {100.f, -100.f, 0.f, 0.f};
	
	float XStraightOffset [4] = {0.f, 0.f, 70.f, -70.f};
	float YStraightOffset [4] = {70.f, -70.f, 0.f, 0.f};
	
	float XDiagonalOffset [4] = {60.f, 60.f, -60.f, -60.f};
	float YDiagonalOffset [4] = {60.f, -60.f, 60.f, -60.f};
	
	int StepOffsetStraightX[4] = {0, 0, GRID_SIZE, -GRID_SIZE};
	int StepOffsetStraightY[4] = {GRID_SIZE, -GRID_SIZE, 0, 0};

	int StepOffsetDiagonalX[4] = {GRID_SIZE, GRID_SIZE, -GRID_SIZE, -GRID_SIZE};
	int StepOffsetDiagonalY[4] = {GRID_SIZE, -GRID_SIZE, GRID_SIZE, -GRID_SIZE};

	TArray<FVector> XYLimits;

	TArray<AActor*> SpawnedActors;

	
	float PositionOnDirection(FVector PPiece, int Pos);
	bool IsInSameGrid(FVector CurrentPosition, FVector TargetPosition);
	
public:
	
	virtual void BeginPlay() override;

	void ClearSpawnedMovementIndicators();

	bool IsValidMoveTarget(FVector HitLocation);

	void DisplayMoves(FVector Start, EPieceType PieceType, EColour PieceColour);
};
