// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"
#include "common.h"
#include "KnightController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KNIGHTVSRED_API UKnightController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKnightController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	template <class T>
	T* FindComponentByClass()
	{
		return Cast<T>(GetOwner()->GetComponentByClass(T::StaticClass()));
	}
	
public:
	UPaperFlipbook* idleAnim;
	UPaperFlipbook* runningAnim;

	APaperFlipbookActor* actor;
	UPaperFlipbookComponent* flipbookComponent;
};
