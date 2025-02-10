// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

// Extra includes

#include "NNGameState.generated.h"

// Forward declares
//class ANNGameMode;

/**
 *  Custom Game State (Generic)
 *
 *  This is meant to hold & manage :
 *   - Level state
 *   - Level accesses
 *   - Level difficulty
 *   - ...
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_GameState, Log, All);

UCLASS()
class NOTNOBANOMENT_API ANNGameState : public AGameStateBase
{
	GENERATED_BODY()

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	ANNGameState();
	~ANNGameState();
};
