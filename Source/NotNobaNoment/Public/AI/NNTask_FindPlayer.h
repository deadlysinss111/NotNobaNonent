// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NNTask_FindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNTask_FindPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UNNTask_FindPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
