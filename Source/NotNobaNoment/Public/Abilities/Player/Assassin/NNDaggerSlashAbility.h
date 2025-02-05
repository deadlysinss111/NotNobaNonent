// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NNAbility.h"
#include "NiagaraComponent.h"
#include "NNDagger.h"
#include "NNDaggerSlashAbility.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNDaggerSlashAbility : public UNNAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	ANNDagger* _dagger;

private:
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* _slashFX;

public:
	UFUNCTION()
	void Init(APawn* owner) override;

	UFUNCTION()
	void Trigger() override;
};
