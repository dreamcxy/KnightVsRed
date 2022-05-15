// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightPawn.h"


// Sets default values
AKnightPawn::AKnightPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct AnimConstructor
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> idleAnim;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> runningAnim;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> attackAnim;
		
		AnimConstructor():
		idleAnim(TEXT("PaperFlipbook'/Game/animation/_Idle_idle._Idle_idle'")),
		runningAnim(TEXT("PaperFlipbook'/Game/animation/_Run_run._Run_run'")),
		attackAnim(TEXT("PaperFlipbook'/Game/animation/_Attack_attack._Attack_attack'"))
		{
			
		}
	};
	static AnimConstructor animConstructor;
	idleAnim = animConstructor.idleAnim.Get();
	runningAnim = animConstructor.runningAnim.Get();
	attackAnim = animConstructor.attackAnim.Get();
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
		const FVector newLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		// print_temp("new location :%s", *(newLocation.ToString()));
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void AKnightPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent->BindAxis("xAxis", this, &AKnightPawn::MoveXAxis);
	// 移动
	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &AKnightPawn::MoveForward);
	PlayerInputComponent->BindAction("MoveBack", IE_Pressed, this, &AKnightPawn::MoveBack);

	PlayerInputComponent->BindAction("MoveForward", IE_Released, this, &AKnightPawn::StopMove);
	PlayerInputComponent->BindAction("MoveBack", IE_Released, this, &AKnightPawn::StopMove);
	
	// 攻击
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKnightPawn::Attack);
	// PlayerInputComponent->BindAction("Attack", IE_Released, this, &AKnightPawn::StopAttack);
	
}

void AKnightPawn::Attack()
{
	if (GetPlayerPawnState() == RUN)
	{
		return;
	}
	TRUE_ERR(ChangeFlipBook(attackAnim), u"Attack");
}

void AKnightPawn::StopAttack()
{
	TRUE_ERR(ChangeFlipBook(idleAnim), u"Attack");
}


void AKnightPawn::MoveForward()
{
	CurrentVelocity.X = FMath::Clamp(MOVE_SPEED, -1.0f, 1.0f) * MOVE_SPEED_MULTI;
	TRUE_ERR(ChangeFlipBook(runningAnim), u"ChangeFlipBook");
	print_temp("rotation:%s", *GetControlRotation().ToString());
	if (!PaperFlipbookComponent->GetComponentRotation().IsZero())
	{
		// 说明方向反了，需要转向
		const FRotator yawRotation(0, 0, 0);
		PaperFlipbookComponent->SetRelativeRotation(yawRotation);
	}
}

void AKnightPawn::MoveBack()
{
	CurrentVelocity.X = FMath::Clamp(-MOVE_SPEED, -1.0f, 1.0f) * MOVE_SPEED_MULTI;
	TRUE_ERR(ChangeFlipBook(runningAnim), u"ChangeFlipBook");
	print_temp("rotation:%s", *GetControlRotation().ToString());
	if (PaperFlipbookComponent->GetComponentRotation().IsZero())
	{
		const FRotator yawRotation(0, 180, 0);
		PaperFlipbookComponent->SetRelativeRotation(yawRotation);
	}
}

void AKnightPawn::StopMove()
{
	CurrentVelocity = FVector::ZeroVector;
	TRUE_ERR(ChangeFlipBook(idleAnim), u"ChangeFlipBook");
}

bool AKnightPawn::ChangeFlipBook(UPaperFlipbook* newPaperFlipbook) const
{
	return PaperFlipbookComponent->SetFlipbook(newPaperFlipbook);
}

void AKnightPawn::SetPlayerPawnState(::PlayerPawnState toState)
{
	if (GetPlayerPawnState() == RUN)
	{
		if (toState == ATTACK)
		{
			return;
		}
	}
}


// void AKnightPawn::MoveXAxis(float value)
// 这个是持续前进
// {
// 	if (value == 0)
// 	{
// 		return;
// 	}
// 	
// 	CurrentVelocity.X = FMath::Clamp(value, -1.0f, 1.0f) * 100.0f;
// 	print_temp("velocity x:%f, y:%f, z:%f", CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);
// 	if (!PaperFlipbookComponent->SetFlipbook(runningAnim))
// 	{
// 		print_err("knight change flip error");
// 	}
// }



