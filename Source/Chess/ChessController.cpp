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
	FVector WorldLocation;
	FVector WorldDirection;
	ECollisionChannel Collision;
	FHitResult HitResult;
	
	if  (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *WorldLocation.ToString());
	}
	if (GetHitResultUnderCursor(Collision, true, HitResult))
	{
		
	}
}

