// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NNTask_FindCover.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNTask_FindCover : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UNNTask_FindCover();
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    FVector FindBestCover(AActor* SelfActor, FVector EnemyLocation);
    bool IsCoverHidden(FVector CoverLocation, AActor* Player, AActor* SelfActor);
};
