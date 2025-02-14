// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NNEnemyAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NNJump.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNJump : public UNNEnemyAbility
{
	GENERATED_BODY()

public:
	void Init(APawn* owner) override;
	void Trigger() override;

	void OnDelayOver();

private:
	UPROPERTY();
	TArray<AActor*> _ObjectsHitOnTheFly;
	
private:
	void OnActorEnter(AActor* OtherActor);
};
