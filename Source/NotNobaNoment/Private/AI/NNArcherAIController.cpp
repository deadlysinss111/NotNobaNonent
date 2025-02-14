// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NNArcherAIController.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include <Abilities/NNFireAbitity.h>
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


ANNArcherAIController::ANNArcherAIController()
{
    // Configurer la perception
    _perceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
    _sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    _sightConfig->SightRadius = 1200.0f;
    _sightConfig->LoseSightRadius = 1500.0f;
    _sightConfig->PeripheralVisionAngleDegrees = 90.0f;
    _sightConfig->SetMaxAge(5.0f);
    _sightConfig->DetectionByAffiliation.bDetectEnemies = true;
    _sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    _sightConfig->DetectionByAffiliation.bDetectFriendlies = false;

    _perceptionComponent->ConfigureSense(*_sightConfig);
    _perceptionComponent->SetDominantSense(*_sightConfig->GetSenseImplementation());
    _perceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANNArcherAIController::OnTargetDetected);
}

void ANNArcherAIController::BeginPlay()
{
    Super::BeginPlay();

    if (_behaviorTree)
    {
        UseBlackboard(_behaviorTree->BlackboardAsset, _blackboardComp);
        RunBehaviorTree(_behaviorTree);
    }
    else
	{
		UE_LOG(LogTemp, Error, TEXT("No behavior tree found for %s"), *GetName());
	}

    if (_abilitySet != NULL) {

        _ability_1 = NewObject<UNNAbility>(this, _abilitySet->_ability_1);
        _ability_1->Init(Cast<APawn>(this));
        UNNFireAbitity* abilityTemp = Cast<UNNFireAbitity>(_ability_1);
        abilityTemp->_BPArrow = ActorBP;
    }
    else
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("the ability set is null"));

    if (!ActorBP)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("the projectil actor is null"));
    }
}

void ANNArcherAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
    if (_blackboardComp)
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            _blackboardComp->SetValueAsObject("Target", Actor);
            //LOG
        }
        else
        {
            _blackboardComp->ClearValue("Target");
        }
    }
    else
	{
		UE_LOG(LogTemp, Error, TEXT("No blackboard component found for %s"), *GetName());
	}
}