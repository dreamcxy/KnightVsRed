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
		idleAnim(TEXT("PaperFlipbook'/Game/animation/knight/_Idle_idle._Idle_idle'")),
		runningAnim(TEXT("PaperFlipbook'/Game/animation/knight/_Run_run._Run_run'")),
		attackAnim(TEXT("PaperFlipbook'/Game/animation/knight/_Attack_attack._Attack_attack'"))
		{
			
		}
	};
	static AnimConstructor animConstructor;
	idleAnim = animConstructor.idleAnim.Get();
	runningAnim = animConstructor.runningAnim.Get();
	attackAnim = animConstructor.attackAnim.Get();

	
}

void AKnightPawn::PrintComponents()
{
	auto components = GetComponents();
	for (auto component : components)
	{
		print_temp("component name:%s", *(component->GetName()));
	}
}


// Called when the game starts or when spawned
void AKnightPawn::BeginPlay()
{
	Super::BeginPlay();

	PaperFlipbookComponent = Cast<UPaperFlipbookComponent>(GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
	NULL_ERR(PaperFlipbookComponent);

	attackRangeBox = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));
	NULL_ERR(attackRangeBox);
	attackRangeBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FScriptDelegate overlayBeginFunc;
	overlayBeginFunc.BindUFunction(this, "OnOverlayBegin");
	attackRangeBox->OnComponentBeginOverlap.Add(overlayBeginFunc);
	// SetPlayerPawnState(IDLE);

	// selfBox = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));
	// NULL_ERR(selfBox);
	// FScriptDelegate overlayBeginFunc;
	// overlayBeginFunc.BindUFunction(this, "OnOverlapBegin");
	// selfBox->OnComponentBeginOverlap.Add(overlayBeginFunc);
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

	ChoosePaperFlipbookByState();
}

// Called to bind functionality to input
void AKnightPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// PlayerInputComponent->BindAxis("xAxis", this, &AKnightPawn::MoveXAxis);
	// 移动
	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &AKnightPawn::MoveForwardByPress);
	PlayerInputComponent->BindAction("MoveBack", IE_Pressed, this, &AKnightPawn::MoveBack);

	PlayerInputComponent->BindAction("MoveForward", IE_Released, this, &AKnightPawn::StopMove);
	PlayerInputComponent->BindAction("MoveBack", IE_Released, this, &AKnightPawn::StopMove);
	
	// 攻击
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKnightPawn::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AKnightPawn::StopAttack);
	
}

void AKnightPawn::Attack()
{
	if (GetPlayerPawnState() == RUN)
	{
		return;
	}
	TRUE_ERR(ChangeFlipBook(attackAnim), u"AttackOn");
	// PaperFlipbookComponent->SetFlipbook(attackAnim);
	// PaperFlipbookComponent->SetLooping(false);
	SetPlayerPawnState(ATTACK);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKnightPawn::FormerAttackJudge, 0.01f, false);
}

void AKnightPawn::FormerAttackJudge()
{
	attackRangeBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (attackRangeBox != nullptr)
	{
		return;
	}
	PRINT_SCREEN(1 ,"attacking");
	// PrintComponents();
}

void AKnightPawn::OnOverlayBegin(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	print_temp("overlap begin");
}




void AKnightPawn::StopAttack()
{
	if (GetPlayerPawnState() != ATTACK)
	{
		return;
	}
	// if (PaperFlipbookComponent->IsPlaying())
	// {
	// 	return;
	// }
	
	// PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &AKnightPawn::SwitchPaperFlipAfterPlay);
	TRUE_ERR(ChangeFlipBook(idleAnim), u"AttackOver");
	SetPlayerPawnState(IDLE);
	attackRangeBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}


void AKnightPawn::MoveForwardByPress()
{
	CurrentVelocity.X = FMath::Clamp(MOVE_SPEED, -1.0f, 1.0f) * MOVE_SPEED_MULTI;
	TRUE_ERR(ChangeFlipBook(runningAnim), u"ChangeFlipBook");
	
	if (!PaperFlipbookComponent->GetComponentRotation().IsZero())
	{
		// 说明方向反了，需要转向
		const FRotator yawRotation(0, 0, 0);
		PaperFlipbookComponent->SetRelativeRotation(yawRotation);
	}
	SetPlayerPawnState(RUN);
	isRunnig = true;
}

void AKnightPawn::MoveBack()
{
	CurrentVelocity.X = FMath::Clamp(-MOVE_SPEED, -1.0f, 1.0f) * MOVE_SPEED_MULTI;
	TRUE_ERR(ChangeFlipBook(runningAnim), u"ChangeFlipBook");
	
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
	isRunnig = false;
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
	PlayerPawnState = toState;
}

void AKnightPawn::SwitchPaperFlipAfterPlay()
{
	print_temp("attack over, switch to idle");
	SetPlayerPawnState(IDLE);
}

void AKnightPawn::ChoosePaperFlipbookByState()
{
	
	// GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, FString::FromInt(GetPlayerPawnState()));

	PRINT_SCREEN(0, "state:%d", GetPlayerPawnState());
	
	switch (GetPlayerPawnState())
	{
	case IDLE:
		if (PaperFlipbookComponent->GetFlipbook() != idleAnim)
		{
			PaperFlipbookComponent->SetFlipbook(idleAnim);
		}
		if (!PaperFlipbookComponent->IsLooping())
		{
			PaperFlipbookComponent->SetLooping(true);
		}
		break;
	
	case RUN:
		if (PaperFlipbookComponent->GetFlipbook() != runningAnim)
		{
			PaperFlipbookComponent->SetFlipbook(runningAnim);
		}
		if (!PaperFlipbookComponent->IsLooping())
		{
			PaperFlipbookComponent->SetLooping(true);
		}
		break;
	default:
		break;
	}
}
