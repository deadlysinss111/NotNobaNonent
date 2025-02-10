// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/NNAbility.h"
#include "NNAbilitySetDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNAbilitySetDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNNAbility> _ability_1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNNAbility> _ability_2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UNNAbility> _ability_3;
	
};
