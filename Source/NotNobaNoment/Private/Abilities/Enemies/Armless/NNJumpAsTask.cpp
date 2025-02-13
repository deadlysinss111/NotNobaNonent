// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Enemies/Armless/NNJumpAsTask.h"

AIMODULE_API UNNJumpAsTask::EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("in progress"));

	return NodeResult;
}