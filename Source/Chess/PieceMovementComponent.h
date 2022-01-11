// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessRuleSubsystem.h"
#include "Piece.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PieceMovementComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHESS_API UPieceMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPieceMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	float TimeToMove;

	FVector InitialPosition;

	FVector EndPosition;

	float TimePassed;

	bool bMoved;

	FVector CurrentGrid;

	UPROPERTY(EditAnywhere)
	EColour Colour;

	UPROPERTY(EditAnywhere)
	EPieceType Piece_Type;

	EPieceState PieceState = static_cast<EPieceState>(0);

	UChessRuleSubsystem* ChessRuleSubsystem = nullptr;

	APiece* Piece;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SetEndPosition(FVector Pos);

	bool GetMoved() { return bMoved; }

	void SetMoved();
	
	void Selected();

	void Attack(UPieceMovementComponent* Piece, AActor* Actor);

	EColour GetColour() { return Colour; }

	FVector GetGridPosition();

	DECLARE_EVENT_TwoParams(UPieceMovementComponent, EPieceStateChange, EColour Colour, EPieceState PieceState);
	EPieceStateChange& OnStateChanged() { return PieceStateChange; }
	
	EPieceStateChange PieceStateChange;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
