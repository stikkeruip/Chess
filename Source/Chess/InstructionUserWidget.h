// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InstructionUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API UInstructionUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInstruction(FString NewInstruction) { Instruction = NewInstruction; }

	UFUNCTION(BlueprintCallable)
		FString GetInstruction() { return Instruction; }

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateInstruction();
	
protected:
	FString Instruction = "Select a Colour";
};
