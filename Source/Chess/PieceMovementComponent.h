// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PieceMovementComponent.generated.h"

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
};


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

	bool bMoving;

	int FinalGridX;
	
	int FinalGridY;

	int CurrentGridX;
	
	int CurrentGridY;

	FVector CurrentGrid;

	UPROPERTY(EditAnywhere)
		EColour Colour;

	UPROPERTY(EditAnywhere)
		EPieceType Piece_Type;

	EPieceState PieceState = static_cast<EPieceState>(0);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SetEndPosition(FVector Pos);

	void Moved();

	bool GetMoving() { return bMoving; }
	
	void Selected();

	FVector GetGridPosition(FVector Pos);

	bool CheckMovementValid(EPieceType PieceType, float F_X, float F_Y);

	DECLARE_EVENT_TwoParams(UPieceMovementComponent, EPieceStateChange, EColour Colour, EPieceState PieceState);
	EPieceStateChange& OnStateChanged() { return PieceStateChange; }
	
	EPieceStateChange PieceStateChange;
};
