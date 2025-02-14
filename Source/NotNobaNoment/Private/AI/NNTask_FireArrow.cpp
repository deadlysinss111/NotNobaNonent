// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NNTask_FireArrow.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include <Abilities/NNFireAbitity.h>
#include <AI/NNArcherAIController.h>

UNNTask_FireArrow::UNNTask_FireArrow()
{
	NodeName = "Fire Arrow";
}

EBTNodeResult::Type UNNTask_FireArrow::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    ACharacter* Archer = Cast<ACharacter>(AIController->GetPawn());
    if (!Archer) return EBTNodeResult::Failed;

	AActor* Target = UGameplayStatics::GetPlayerPawn(AIController->GetPawn(), 0);
	if (!Target) return EBTNodeResult::Failed;

    AActor* ArcherActor = Cast<AActor>(Archer);
    if (!ArcherActor || !CanSeeTarget(ArcherActor, Target)) return EBTNodeResult::Failed;

	FVector MyLocation = Archer->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	// Vérifier la distance de tir
	float Distance = FVector::Distance(MyLocation, TargetLocation);
	if (Distance > 1000) return EBTNodeResult::Failed;

    //LOG
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Fire Arrow"));

	Fire(ArcherActor, Target);

    return EBTNodeResult::Succeeded;
}

bool UNNTask_FireArrow::CanSeeTarget(AActor* SelfActor, AActor* Target)
{
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(SelfActor);

    bool bHit = SelfActor->GetWorld()->LineTraceSingleByChannel(
        HitResult,
        SelfActor->GetActorLocation(),
        Target->GetActorLocation(),
        ECC_Visibility,
        QueryParams
    );

    return !bHit || HitResult.GetActor() == Target;
}

void UNNTask_FireArrow::Fire(AActor* SelfActor, AActor* Target)
{
	if (!SelfActor || !Target) return;

	FVector direction = Target->GetActorLocation() - SelfActor->GetActorLocation();

	UActorComponent* component = SelfActor->FindComponentByTag(UActorComponent::StaticClass(), "spawnPoint");

	if (USceneComponent* SceneComp = Cast<USceneComponent>(component))
	{
		//LOG
		UE_LOG(LogTemp, Warning, TEXT("Spawn"));
		GetWorld()->SpawnActor<AActor>(ActorBP, SceneComp->GetComponentLocation(), direction.ToOrientationRotator());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No spawn point found"));
	}
}


