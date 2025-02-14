// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include <Abilities/NNAbilitySetDataAsset.h>
#include "NNTask_FireArrow.generated.h"



/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNTask_FireArrow : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNNTask_FireArrow();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorBP;

private:

	bool CanSeeTarget(AActor* SelfActor, AActor* Target);
	void Fire(AActor* SelfActor, AActor* Target);
};
