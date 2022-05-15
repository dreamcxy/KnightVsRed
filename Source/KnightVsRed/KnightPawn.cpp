// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightPawn.h"

#include "common.h"

// Sets default values
AKnightPawn::AKnightPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKnightPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnightPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKnightPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("xAxis", this, &AKnightPawn::MoveXAxis);
}

void AKnightPawn::MoveXAxis(float value)
{
	if (value != 0)
	{
		print_temp("move xaxis");
	}
	
}



