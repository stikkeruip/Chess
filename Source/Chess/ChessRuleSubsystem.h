// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstructionUserWidget.h"
#include "Subsystems/WorldSubsystem.h"
#include <vector>
#include "GameFramework/GameModeBase.h"
#include "ChessRuleSubsystem.generated.h"

class AChessPlayer;

/**
 * 
 */

UENUM()
enum class EColour
{
	C_Black = 0	UMETA(DisplayName = "Black"),
	C_White = 1	UMETA(DisplayName = "White"),
};

UENUM()
enum class EPieceState
{
	PS_Unselected = 0	UMETA(DisplayName = "Unselected"),
	PS_Selected = 1		UMETA(DisplayName = "Selected"),
	PS_Moving = 2		UMETA(DisplayName = "Moving"),
};

UENUM()
enum class EPieceType
{
	PT_Pawn = 0		UMETA(DisplayName = "Pawn"),
	PT_Castle = 1	UMETA(DisplayName = "Castle"),
	PT_Bishop = 2	UMETA(DisplayName = "Bishop"),
	PT_Queen = 3	UMETA(DisplayName = "Queen"),
	PT_Knight = 4	UMETA(DisplayName = "Knight"),
	PT_King = 5		UMETA(DisplayName = "King")
};

class UPieceMovementComponent;

UCLASS()
class CHESS_API UChessRuleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateInstructionWidget(TSubclassOf<UUserWidget> InstructionWidgetClass);
	
	void DisplayInstructionWidget();
	
	void InstructionCompleted(EColour Colour, EPieceState PieceState);

	bool CheckMovementValid(EPieceType PieceType, EColour Colour, float F_X, float F_Y, FVector CurrentGrid);

	void AddPiece(UPieceMovementComponent* Piece);

	void RemovePiece(UPieceMovementComponent* Piece);

	void EndTurn(EColour Colour);

	EColour GetTurn() { return CurrentColour; }

	AChessPlayer* ChessPlayer;

private:
	
	UInstructionUserWidget* InstructionWidget = nullptr;

	std::vector<UPieceMovementComponent*> Pieces;

	EColour CurrentColour = EColour::C_White;
};

