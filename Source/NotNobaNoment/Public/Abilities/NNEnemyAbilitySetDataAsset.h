// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/NNEnemyAbility.h"
#include "NNEnemyAbilitySetDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNEnemyAbilitySetDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UNNEnemyAbility>> _abilities;
	
};
