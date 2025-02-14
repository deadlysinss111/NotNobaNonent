// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Abilities/NNAbility.h"
#include "Abilities/NNAbilitySetDataAsset.h"
#include <Perception/AIPerceptionTypes.h>
#include "NNArcherAIController.generated.h"


/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API ANNArcherAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	ANNArcherAIController();

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

private:
		
	UPROPERTY(VisibleAnywhere, Category = "Perception")
	class UAIPerceptionComponent* _perceptionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Perception")
	class UAISenseConfig_Sight* _sightConfig;

	//Behavior Tree
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	class UBehaviorTree* _behaviorTree;

	//Blackboard
	UPROPERTY(EditAnywhere, Category = "Behavior Tree")
	class UBlackboardComponent* _blackboardComp;
		
		
	FTimerHandle _timerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate = 2.0f; // Une flèche toutes les 2 secondes
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float OptimalRange = 800.0f; // Distance idéale pour tirer

	APawn* TargetEnemy;

public:
	UPROPERTY(EditAnywhere)
	UNNAbilitySetDataAsset* _abilitySet;

	UPROPERTY()
	UNNAbility* _ability_1;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<AActor> ActorBP;

};
