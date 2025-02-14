// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NNAbility.h"
#include "NiagaraComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "NNSmokeAbility.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNSmokeAbility : public UNNAbility
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float duration = 4;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* _smokeFX;
	UNiagaraComponent* _smokeInstance;

public:
	void Init(APawn* owner) override;
	void Trigger(KeyState state) override;

	UFUNCTION()
	void SetBackVisibility();
};
