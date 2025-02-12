// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NNCanMoveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNNCanMoveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NOTNOBANOMENT_API INNCanMoveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Move(FVector direction, float speed) = 0;
};
