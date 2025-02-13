// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NNAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NNJump.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNJump : public UNNAbility
{
	GENERATED_BODY()

public:
	void Init(APawn* owner) override;
	void Trigger(KeyState state) override;

	void OnDelayOver();

private:
	UPROPERTY();
	TArray<AActor*> _ObjectsHitOnTheFly;
	
private:
	void OnActorEnter(AActor* OtherActor);
};
