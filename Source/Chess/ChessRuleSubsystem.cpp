// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRuleSubsystem.h"

#include "PieceMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ChessPlayer.h"

void UChessRuleSubsystem::CreateInstructionWidget(TSubclassOf<UUserWidget> InstructionWidgetClass)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	InstructionWidget = CreateWidget<UInstructionUserWidget>(PlayerController, InstructionWidgetClass);
}

void UChessRuleSubsystem::DisplayInstructionWidget()
{
	ensureMsgf(InstructionWidget, TEXT("InstructionWidget is nullptr"));
	InstructionWidget->AddToViewport();
}

void UChessRuleSubsystem::InstructionCompleted(EColour Colour, EPieceState PieceState)
{
	if(CurrentColour == EColour::C_Black)
	{
		InstructionWidget->SetInstruction(TEXT("Black Turn"));
		UE_LOG(LogTemp, Warning, TEXT("black"));
	}
	if(CurrentColour == EColour::C_White)
	{
		InstructionWidget->SetInstruction(TEXT("White Turn"));
		UE_LOG(LogTemp, Warning, TEXT("white"));
	}
}

void UChessRuleSubsystem::EndTurn(EColour Colour)
{
	Colour == EColour::C_White ? CurrentColour = EColour::C_Black : CurrentColour = EColour::C_White;

	if(CurrentColour == EColour::C_White)
	{
		ChessPlayer->CameraWhite();
	}
	if(CurrentColour == EColour::C_Black)
	{
		ChessPlayer->CameraBlack();
	}
}


bool UChessRuleSubsystem::CheckMovementValid(EColour Colour)
{
	if(Colour == CurrentColour)
	{
		return true;
	}

	return false;
}

void UChessRuleSubsystem::AddPiece(UPieceMovementComponent* Piece)
{
	Pieces.push_back(Piece);
}

void UChessRuleSubsystem::RemovePiece(UPieceMovementComponent* Piece)
{
	auto i = std::find(Pieces.begin(), Pieces.end(), Piece);

	Pieces.erase(i);
}
