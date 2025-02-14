// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NNTask_FindPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


UNNTask_FindPlayer::UNNTask_FindPlayer()
{
	NodeName = "Find Player";
}

EBTNodeResult::Type UNNTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    OwnerComp.GetWorld()->GetTimerManager().SetTimerForNextTick([this, &OwnerComp]()
    {
        ExecuteTask(OwnerComp, nullptr);
    });

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(AIController->GetPawn(), 0);
        if (PlayerPawn)
        {
            FVector PlayerLocation = PlayerPawn->GetActorLocation();
            OwnerComp.GetBlackboardComponent()->SetValueAsVector("Target", PlayerLocation);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}