// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

// Extra includes

#include "NNGameStatePlaying.generated.h"

/**
 *  Custom Game State (Currently Playing through a level)
 * 
 *  This is meant to hold & manage :
 *   - Level state
 *   - Level accesses
 *   - Level difficulty
 *   - ...
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_GameStatePlaying, Log, All);

UCLASS()
class NOTNOBANOMENT_API ANNGameStatePlaying : public AGameStateBase
{
	GENERATED_BODY()

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	ANNGameStatePlaying();
	~ANNGameStatePlaying();
};
