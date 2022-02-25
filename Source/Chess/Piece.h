// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessRuleSubsystem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UCLASS()
class CHESS_API APiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPieceMovementComponent* MovementComponent;

	UMaterialInterface* MaterialB;
	UMaterialInterface* MaterialW;
	
	UMaterialInterface* MaterialB_P;
	UMaterialInterface* MaterialW_P;
	
	USkeletalMesh* PawnMesh;
	USkeletalMesh* CastleMesh;
	USkeletalMesh* BishopMesh;
	USkeletalMesh* QueenMesh;
	USkeletalMesh* KingMesh;
	USkeletalMesh* KnightMesh;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void ChangeMaterial(EColour Colour, EPieceType Piece);

	void ChangeMesh(EPieceType Piece);

	bool GetFirstMove();
};
