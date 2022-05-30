// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KnightPawn.h"	
#include "KVRGameController.generated.h"

/**
 * 
 */
UCLASS()
class KNIGHTVSRED_API AKVRGameController : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="GameSetting")
	FVector bluePoint;		// 蓝色方
	FVector redPoint;		// 红色方
	
private:
	
	
};
