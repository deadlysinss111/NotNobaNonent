// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NNJumpAsTask.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNJumpAsTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UNNJumpAsTask();

private:
	bool _jumpCond = false;
	bool _stopCond = false;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void OnDelayOver();
};
