// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessRuleSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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
	if(Colour == EColour::C_Black)
	{
		InstructionWidget->SetInstruction(TEXT("Move the black piece"));
		UE_LOG(LogTemp, Warning, TEXT("black"));
	}
	if(Colour == EColour::C_White)
	{
		InstructionWidget->SetInstruction(TEXT("Move the white piece"));
		UE_LOG(LogTemp, Warning, TEXT("white"));
	}
}
