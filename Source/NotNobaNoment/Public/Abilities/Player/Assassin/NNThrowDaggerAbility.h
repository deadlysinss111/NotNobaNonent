// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NNAbility.h"
#include "NNThrowDaggerAbility.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNThrowDaggerAbility : public UNNAbility
{
	GENERATED_BODY()

private:
	bool _isGrounded;
	
public:
	void Init(APawn* owner) override;
	void Trigger() override;
	void Throw();
	void Jump();

};
