// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NNEntityCharacter.h"
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

protected:
	virtual void Tick(float DeltaTime) override;
	
public:
	virtual void KnockBack(AActor* OtherActor);
};
