// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessController.h"

void AChessController::SetupInputComponent()
{
	Super::SetupInputComponent();

	bEnableClickEvents = true;

	bShowMouseCursor = true;

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &AChessController::OnMouseClick);
}

void AChessController::OnMouseClick()
{
	UE_LOG(LogTemp, Warning, TEXT("clicked"));
}

