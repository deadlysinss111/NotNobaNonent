// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/NNEntityInterface.h"
#include <functional>
#include "NNDagger.generated.h"

UCLASS()
class NOTNOBANOMENT_API ANNDagger : public AActor, public INNEntityInterface
{
	GENERATED_BODY()

public:
	enum class DaggerState
	{
		Handed = 0,
		Hitting,
		Flying,
		Grounded,
	};
	
public:	
	ANNDagger();

public:
	DaggerState _currentState;
	//void(*_currentStateAction)(AActor* OtherActor);
	std::function<void(AActor*)> _currentStateAction;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnActorEnter(AActor* OtherActor) override;


public:
	void ChangeState(DaggerState newState);

	void HandedOverlapAction(AActor* OtherActor);
	void HittingOverlapAction(AActor* OtherActor);
	void FlyingOverlapAction(AActor* OtherActor);
	void GroundedOverlapAction(AActor* OtherActor);

	void Slash();
	void Throw();
};
