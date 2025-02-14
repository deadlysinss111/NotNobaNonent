// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NNTask_FindCover.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NavigationSystem.h"


UNNTask_FindCover::UNNTask_FindCover()
{
	NodeName = "Find Cover";
}

EBTNodeResult::Type UNNTask_FindCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    OwnerComp.GetWorld()->GetTimerManager().SetTimerForNextTick([this, &OwnerComp]()
    {
        ExecuteTask(OwnerComp, nullptr);
    });

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    APawn* SelfPawn = AIController->GetPawn();
    if (!SelfPawn) return EBTNodeResult::Failed;

    // Récupérer la position du joueur
    AActor* Player = UGameplayStatics::GetPlayerPawn(AIController->GetPawn(), 0);

    if (!Player)
    {
        return EBTNodeResult::Failed;
    }

   
    FVector CoverLocation = FindBestCover(SelfPawn, Player->GetActorLocation());
    if (CoverLocation == FVector::ZeroVector) return EBTNodeResult::Failed;

    // Mettre à jour le Blackboard
    OwnerComp.GetBlackboardComponent()->SetValueAsVector("CoverLocation", CoverLocation);
    return EBTNodeResult::Succeeded;
}

FVector UNNTask_FindCover::FindBestCover(AActor* SelfActor, FVector EnemyLocation)
{
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(SelfActor);
    if (!NavSystem) return FVector::ZeroVector;

    AActor* Player = UGameplayStatics::GetPlayerPawn(SelfActor->GetWorld(), 0);
    if (!Player) return FVector::ZeroVector;

    FVector BestCover = FVector::ZeroVector;
    float BestDistance = FLT_MAX;

    for (int i = 0; i < 10; i++) 
    {
        FVector TestLocation = SelfActor->GetActorLocation() + (EnemyLocation - SelfActor->GetActorLocation()).GetSafeNormal() * 400.0f + FMath::VRand() * 200.0f;
        FNavLocation NavPoint;


        if (NavSystem->GetRandomPointInNavigableRadius(TestLocation, 300.0f, NavPoint))
        {
            if (IsCoverHidden(NavPoint.Location, Player, SelfActor))
            {

                float DistToEnemy = FVector::Dist(NavPoint.Location, EnemyLocation);
                if (DistToEnemy > 200 && DistToEnemy < BestDistance) 
                {
                    BestCover = NavPoint.Location;
                    BestDistance = DistToEnemy;
                }
            }
        }
    }

    return BestCover;
}

bool UNNTask_FindCover::IsCoverHidden(FVector CoverLocation, AActor* Player, AActor* SelfActor)
{
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Player);
    QueryParams.AddIgnoredActor(SelfActor);

    bool bHit = SelfActor->GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Player->GetActorLocation(),
        CoverLocation,
        ECC_Visibility,
        QueryParams
    );

    return bHit;
}