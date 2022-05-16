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
	SetPlayerPawnState(IDLE);
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
	// print_temp("knight state: %d", GetPlayerPawnState());
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
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AKnightPawn::StopAttack);
	
}

void AKnightPawn::Attack()
{
	print_temp("knight state: %d", GetPlayerPawnState());
	if (GetPlayerPawnState() == RUN)
	{
		return;
	}
	TRUE_ERR(ChangeFlipBook(attackAnim), u"AttackOn");
	SetPlayerPawnState(ATTACK);
}

void AKnightPawn::StopAttack()
{
	if (GetPlayerPawnState() != ATTACK)
	{
		return;
	}
	TRUE_ERR(ChangeFlipBook(idleAnim), u"AttackOver");
	SetPlayerPawnState(IDLE);
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
	SetPlayerPawnState(RUN);
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
	SetPlayerPawnState(RUN);
}

void AKnightPawn::StopMove()
{
	CurrentVelocity = FVector::ZeroVector;
	TRUE_ERR(ChangeFlipBook(idleAnim), u"stopmove");
	SetPlayerPawnState(IDLE);
}

bool AKnightPawn::ChangeFlipBook(UPaperFlipbook* newPaperFlipbook) const
{
	print_temp("change filpbook to : %s", *newPaperFlipbook->GetName());
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
	PlayerPawnState = toState;
}

