// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Essentials/NNGameState.h"

// Extra includes

#include "NNGS_Gameplay.generated.h"


/**
 *  Custom Game State (Gameplay)
 *
 *  This is meant to hold & manage :
 *   - Level state
 *   - Level accesses
 *   - Level difficulty
 *   - ...
 */

DECLARE_LOG_CATEGORY_EXTERN(NNGS_Gameplay, Log, All);

UCLASS()
class NOTNOBANOMENT_API ANNGS_Gameplay : public ANNGameState
{
	GENERATED_BODY()
	
	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	ANNGS_Gameplay();
	~ANNGS_Gameplay();

	// BeginPlay override
	virtual void BeginPlay() override;
};
