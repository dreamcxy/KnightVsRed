// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "common.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "KnightPawn.generated.h"

UCLASS()
class KNIGHTVSRED_API AKnightPawn : public APawn
{
	GENERATED_BODY()

	
	
public:
	// Sets default values for this pawn's properties
	AKnightPawn();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Anims");
	bool isRunnig;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Anims");
	bool isIdle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Anims");
	bool isAttack;
	
	
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
	UFUNCTION(BlueprintCallable)
	void MoveForwardByPress();
	void MoveBack();
	void StopMove();
	void Attack();
	void StopAttack();

	void FormerAttackJudge();
	
	UFUNCTION(Category="CallBack")
	void SwitchPaperFlipAfterPlay();

private:
	bool ChangeFlipBook(UPaperFlipbook* newPaperFlipbook) const;
	void SetPlayerPawnState(PlayerPawnState toState);
	PlayerPawnState GetPlayerPawnState() const { return PlayerPawnState; }
	void ChoosePaperFlipbookByState();

	void PrintComponents();
	
	// 碰撞检测
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent *OnComponentBeginOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
public:
	FVector CurrentVelocity;
	FTimerHandle TimerHandle;
	
	UBoxComponent* attackRangeBox = nullptr;
	UBoxComponent* selfBox = nullptr;

	UPaperFlipbookComponent* PaperFlipbookComponent;
	UPaperFlipbook* idleAnim;
	UPaperFlipbook* runningAnim;
	UPaperFlipbook* attackAnim;

	PlayerPawnState PlayerPawnState;
};
