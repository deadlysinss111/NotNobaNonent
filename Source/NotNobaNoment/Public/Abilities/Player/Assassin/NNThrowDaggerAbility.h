// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NNAbility.h"
#include "NNDagger.h"
#include "NNThrowDaggerAbility.generated.h"

DECLARE_DYNAMIC_DELEGATE(FActionToTrigger);

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNThrowDaggerAbility : public UNNAbility
{
	GENERATED_BODY()

private:
	FActionToTrigger _currentAction;

	UPROPERTY(EditAnywhere)
	ANNDagger* _dagger;
	
public:
	void Init(APawn* owner) override;
	void Trigger() override;

	UFUNCTION()
	void Throw();
	UFUNCTION()
	void Jump();

};
