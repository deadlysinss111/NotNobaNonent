// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NNEnemyAbility.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNEnemyAbility : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	APawn* _owner;

public:
	UFUNCTION()
	virtual void Init(APawn* owner);

	UFUNCTION(BlueprintCallable)
	virtual void Trigger() {};
};
