// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "common.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KnightVsRedGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class KNIGHTVSRED_API AKnightVsRedGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category="GameModeProperty")
	FVector leftPoint;			// 左边方

	UPROPERTY(EditAnywhere, Category="GameModeProperty")
	FVector rightPoint;			// 右边方


public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override; 
};
