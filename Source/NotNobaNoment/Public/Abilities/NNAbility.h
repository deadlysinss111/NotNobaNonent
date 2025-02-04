// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "GameFramework/Pawn.h"
#include "NNAbility.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	APawn* _owner;

public:
	virtual void Init(APawn* owner);
	virtual void Trigger() {};
	
};
