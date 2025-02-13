// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Enemies/Armless/NNJumpAsTask.h"
#include "Character/NNEnemyCharacter.h"
#include "Character/NNPlayerCharacter.h"
#include "Utility/TrajectoryToolbox.h"
#include "AIController.h"

UNNJumpAsTask::UNNJumpAsTask() {
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UNNJumpAsTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	// Animate spring
	FTimerHandle UnusedHandle;
	OwnerComp.GetOwner()->GetWorldTimerManager().SetTimer(UnusedHandle, this, &UNNJumpAsTask::OnDelayOver, 2, false);

	return NodeResult;
}


void UNNJumpAsTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);

	if (_jumpCond) {
		AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));

		if (target == NULL) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("There was an issue in retrieving the target actor"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
		ANNEnemyCharacter* armless = Cast<ANNEnemyCharacter>(controller->GetPawn());

		if (armless == NULL) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("There was an issue in casting owner into enemy"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		_jumpCond = false;

		
		FVector location = armless->GetActorLocation();
		FVector dist = target->GetActorLocation() - location;
		FVector force = TrajectoryToolbox::BellCurveInitialVelocity(location, location + 2* dist, 150, 1000);

		UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(armless->GetRootComponent());
		PhysComp->AddImpulse(force * dist.Length()/4);
	}

	if (_stopCond) {
		ANNEnemyCharacter* armless = Cast<ANNEnemyCharacter>(OwnerComp.GetOwner());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


void UNNJumpAsTask::OnDelayOver()
{
	_jumpCond = true;
}