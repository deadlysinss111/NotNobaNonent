// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NNEntityCharacter.h"
#include "Abilities/NNEnemyAbility.h"
#include "Abilities/NNEnemyAbilitySetDataAsset.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NNEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API ANNEnemyCharacter : public ANNEntityCharacter
{
	GENERATED_BODY()

protected:
	bool _isBeingKnockbacked = false;
	FVector _KBTargetPos;
	FVector _KBDisplacementPerFrame;
	float _KBLastDist;

	bool _provideContactDamage = true;

public:
	UPROPERTY(EditAnywhere)
	UNNEnemyAbilitySetDataAsset* _abilitySet;

	UPROPERTY(BlueprintReadWrite)
	TArray<UNNEnemyAbility*> _abilities;

public:
	UPROPERTY()
	UBlackboardComponent* _blackBoard;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnActorEnter(AActor* OtherActor) override;
	
public:
	virtual void KnockBack(AActor* OtherActor);
};
