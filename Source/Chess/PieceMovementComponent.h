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
	C_None = 2	UMETA(DisplayName = "None"),
};

UENUM()
enum class EPieceState
{
	PS_Unselected = 0	UMETA(DisplayName = "Unselected"),
	PS_Selected = 1		UMETA(DisplayName = "Selected"),
	PS_Moving = 2		UMETA(DisplayName = "Moving"),
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

	UPROPERTY(EditAnywhere)
		EColour Colour;

	EPieceState PieceState = static_cast<EPieceState>(0);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetEndPosition(FVector Pos);

	void Moved();

	bool GetMoving() { return bMoving; }
	
	void Selected();

	DECLARE_EVENT_TwoParams(UPieceMovementComponent, EPieceStateChange, EColour Colour, EPieceState PieceState);
	EPieceStateChange& OnStateChanged() { return PieceStateChange; }
	
	EPieceStateChange PieceStateChange;
};
