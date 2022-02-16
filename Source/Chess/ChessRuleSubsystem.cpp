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


bool UChessRuleSubsystem::CheckMovementValid(EPieceType PieceType, EColour Colour, float F_X, float F_Y, FVector CurrentGrid)
{
	int CurrentGridX = round(abs(CurrentGrid.X)/100);
	int CurrentGridY = round(abs(CurrentGrid.Y)/100);
	
	F_X = round(abs(F_X)/100);
	F_Y = round(abs(F_Y)/100);

	if(Colour == CurrentColour)
	{
		if (PieceType == EPieceType::PT_Pawn && F_X == CurrentGridX && (F_Y == CurrentGridY + 1 && Colour == EColour::C_White || F_Y == CurrentGridY - 1 && Colour == EColour::C_Black))
		{
			return true;
		}
		if (PieceType == EPieceType::PT_Castle && (F_X >= 1 && F_X <= 8 && F_Y == CurrentGridY || F_Y >= 1 && F_Y <= 8 && F_X == CurrentGridX))
		{
			return true;
		}
		if (PieceType == EPieceType::PT_Bishop && abs(F_X - CurrentGridX) == abs(F_Y - CurrentGridY))
		{
			return true;
		}

		return false;
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
