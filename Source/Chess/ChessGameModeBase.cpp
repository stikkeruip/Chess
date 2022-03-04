// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChessGameModeBase.h"

#include "ChessRuleSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AChessGameModeBase::StartPlay()
{
	Super::StartPlay();
	UChessRuleSubsystem* ChessRuleSubsystem = GetWorld()->GetSubsystem<UChessRuleSubsystem>();

	if(ChessRuleSubsystem)
	{
		ChessRuleSubsystem->CreateInstructionWidget(InstructionWidgetClass);
		ChessRuleSubsystem->DisplayInstructionWidget();
	}

	
}


