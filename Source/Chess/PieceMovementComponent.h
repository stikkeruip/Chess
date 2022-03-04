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

	bool bMoving;

	bool bGoingToAttack;

	bool bAttacking;

	bool bFirstMove;

	FVector CurrentGrid;

	UPROPERTY(EditAnywhere)
	EColour Colour;

	UPROPERTY(EditAnywhere)
	EPieceType Piece_Type;

	UPROPERTY(EditAnywhere)
	UParticleSystem* DestroyedParticleSystem;

	EPieceState PieceState = static_cast<EPieceState>(0);

	UChessRuleSubsystem* ChessRuleSubsystem = nullptr;

	APiece* Piece;

	AActor* AttackedActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SetEndPosition(FVector Pos);

	UFUNCTION(BlueprintCallable)
	bool IsMoving() { return bMoving; }

	UFUNCTION(BlueprintCallable)
	bool IsAttacking() { return bAttacking; }

	UFUNCTION(BlueprintCallable)
	void SetAttacking(bool Attacking) { bAttacking = Attacking; bGoingToAttack = false; bMoving = true;}

	UFUNCTION(BlueprintCallable)
	void DestroyAttackedActor();

	bool GetFirstMove() { return bFirstMove; }
	
	bool CanAttack();

	EPieceType GetPieceType() { return Piece_Type; }

	UFUNCTION(BlueprintCallable)
	void SetMoved();
	
	void Selected();

	void Attack(UPieceMovementComponent* Piece);

	EColour GetColour() { return Colour; }

	FVector GetGridPosition();

	DECLARE_EVENT(UPieceMovementComponent, EPieceStateChange);
	EPieceStateChange& OnStateChanged() { return PieceStateChange; }
	
	EPieceStateChange PieceStateChange;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
