// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstructionUserWidget.h"
#include "Subsystems/WorldSubsystem.h"

#include "PieceMovementComponent.h"

#include "ChessRuleSubsystem.generated.h"

/**
 * 
 */

UCLASS()
class CHESS_API UChessRuleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateInstructionWidget(TSubclassOf<UUserWidget> InstructionWidgetClass);
	void DisplayInstructionWidget();
	
	void InstructionCompleted(EColour Colour, EPieceState PieceState);

private:
	
	UInstructionUserWidget* InstructionWidget = nullptr;
	
};

