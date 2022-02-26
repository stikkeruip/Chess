// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRuleSubsystem.h"

#include "PieceMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ChessPlayer.h"
#include "ChessUtils.h"

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

void UChessRuleSubsystem::InstructionCompleted()
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
	int CurrentGridX = ChessUtils::RoundToGrid(CurrentGrid.X);
	int CurrentGridY = ChessUtils::RoundToGrid(CurrentGrid.Y);
	
	F_X = ChessUtils::RoundToGrid(F_X);
	F_Y = ChessUtils::RoundToGrid(F_Y);

	if(XLimitMax < 0.f)
	{
		XLimitMax = ChessUtils::RoundToGrid(XLimitMax);
		UE_LOG(LogTemp, Warning, TEXT("%f"), XLimitMax)
		XLimitMin = ChessUtils::RoundToGrid(XLimitMin);
		UE_LOG(LogTemp, Warning, TEXT("%f"), XLimitMin)
		YLimitMax = ChessUtils::RoundToGrid(YLimitMax);
		UE_LOG(LogTemp, Warning, TEXT("%f"), YLimitMax)
		YLimitMin = ChessUtils::RoundToGrid(YLimitMin);
		UE_LOG(LogTemp, Warning, TEXT("%f"), YLimitMin)
	}

	if(Colour == CurrentColour)
	{
		if (PieceType == EPieceType::PT_Pawn && F_X == CurrentGridX && ((F_Y == CurrentGridY + 1 || F_Y == CurrentGridY + 2) && Colour == EColour::C_White || (F_Y == CurrentGridY - 1 || F_Y == CurrentGridY - 2) && Colour == EColour::C_Black))
		{
			return true;
		}
		if ((PieceType == EPieceType::PT_Castle || PieceType == EPieceType::PT_Queen) && (F_X >= XLimitMin && F_X <= XLimitMax && F_Y == CurrentGridY || F_Y >= YLimitMin && F_Y <= YLimitMax && F_X == CurrentGridX))
		{
			return true;
		}
		if ((PieceType == EPieceType::PT_Bishop || PieceType == EPieceType::PT_Queen) && abs(F_X - CurrentGridX) == abs(F_Y - CurrentGridY))
		{
			return true;
		}
		if (PieceType == EPieceType::PT_King && F_X == CurrentGridX + 1 || F_Y == CurrentGridY + 1)
		{
			return true;
		}
		if (PieceType == EPieceType::PT_Knight && ((F_X == CurrentGridX + 1 || F_X == CurrentGridX - 1) && (F_Y == CurrentGridY + 2 || F_Y == CurrentGridY - 2) || (F_X == CurrentGridX + 2 || F_X == CurrentGridX - 2) && (F_Y == CurrentGridY + 1 || F_Y == CurrentGridY - 1)))
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
