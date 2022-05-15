// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "common.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "KnightPawn.generated.h"

UCLASS()
class KNIGHTVSRED_API AKnightPawn : public APawn
{
	GENERATED_BODY()

	
	
public:
	// Sets default values for this pawn's properties
	AKnightPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// void MoveXAxis(float value);
	void MoveForward();
	void MoveBack();
	void StopMove();
	void Attack();
	void StopAttack();
	
private:
	bool ChangeFlipBook(UPaperFlipbook* newPaperFlipbook) const;
	void SetPlayerPawnState(PlayerPawnState toState);
	PlayerPawnState GetPlayerPawnState() const { return PlayerPawnState; }
public:
	FVector CurrentVelocity;

	UPaperFlipbookComponent* PaperFlipbookComponent;
	UPaperFlipbook* idleAnim;
	UPaperFlipbook* runningAnim;
	UPaperFlipbook* attackAnim;

	PlayerPawnState PlayerPawnState;

};
