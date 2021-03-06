// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>InstructionWidgetClass;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void GameEndedEvent();
};
