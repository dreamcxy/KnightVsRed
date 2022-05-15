// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightPawn.h"

#include "common.h"

// Sets default values
AKnightPawn::AKnightPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct AnimConstructor
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> idleAnim;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> runningAnim;

		AnimConstructor():
		idleAnim(TEXT("PaperFlipbook'/Game/animation/_Idle_idle._Idle_idle'")),
		runningAnim(TEXT("PaperFlipbook'/Game/animation/_Run_run._Run_run'"))
		{
			
		}
	};
	static AnimConstructor animConstructor;
	idleAnim = animConstructor.idleAnim.Get();
	runningAnim = animConstructor.runningAnim.Get();
}

// Called when the game starts or when spawned
void AKnightPawn::BeginPlay()
{
	Super::BeginPlay();

	// auto components = GetComponents();
	// for (auto component : components)
	// {
	// 	print_temp("component name:%s", *(component->GetName()));
	// }

	PaperFlipbookComponent = Cast<UPaperFlipbookComponent>(GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
	NULL_ERR(PaperFlipbookComponent);
	
}

// Called every frame
void AKnightPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector newLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		print_temp("new location x:%f, y:%f, z:%f", newLocation.X, newLocation.Y, newLocation.Z);
		SetActorLocation(newLocation);
	}

}

// Called to bind functionality to input
void AKnightPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("xAxis", this, &AKnightPawn::MoveXAxis);
	
}

void AKnightPawn::MoveXAxis(float value)
{
	if (value == 0)
	{
		return;
	}
	
	CurrentVelocity.X = FMath::Clamp(value, -1.0f, 1.0f) * 100.0f;
	print_temp("velocity x:%f, y:%f, z:%f", CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);
	if (!PaperFlipbookComponent->SetFlipbook(runningAnim))
	{
		print_err("knight change flip error");
	}
}



