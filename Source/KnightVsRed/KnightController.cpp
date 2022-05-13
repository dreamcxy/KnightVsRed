// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightController.h"


// Sets default values for this component's properties
UKnightController::UKnightController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
	struct AnimContructor
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> idleAnim;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> runnigAnim;

		AnimContructor():
		idleAnim(TEXT("PaperFlipbook'/Game/animation/_Idle_idle._Idle_idle'")),
		runnigAnim(TEXT("PaperFlipbook'/Game/animation/_Run_run._Run_run'"))
		{
			
		}
	};

	static AnimContructor animContructor;
	idleAnim = animContructor.idleAnim.Get();
	runningAnim = animContructor.runnigAnim.Get();
}


// Called when the game starts
void UKnightController::BeginPlay()
{
	Super::BeginPlay();

	// ...

	UE_LOG(LogTemp, Log, TEXT("owner : %s"), *(GetOwner()->GetName()));

	actor = Cast<APaperFlipbookActor>(GetOwner());
	if (UNLIKELY(!actor))
	{
		UE_LOG(LogTemp, Error, TEXT("actor get fail"));
	}
	flipbookComponent = actor->GetRenderComponent();
	if (UNLIKELY(!flipbookComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("flipbookcomponent get fail"));
	}
	UE_LOG(LogTemp, Log, TEXT("flipbook name : %s"), *(flipbookComponent->GetFlipbook()->GetName()));
	if (!flipbookComponent->SetFlipbook(runningAnim))
	{
		UE_LOG(LogTemp, Error, TEXT("set flip book fail"));
	}
	print_temp("after set filpbook name : %s",  *(flipbookComponent->GetFlipbook()->GetName()));
}


// Called every frame
void UKnightController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


