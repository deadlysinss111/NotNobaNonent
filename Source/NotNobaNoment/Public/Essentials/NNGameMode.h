// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// Extra includes
#include "GameFramework/Actor.h"		// Makes Actor handling possible, which is useful immidiately (constructor).
#include "GameFramework/HUD.h"			// Makes HUD handling possible, which is useful immidiately (constructor). Not included above, for some reason.
#include "NNGameStatePlaying.h"
#include "NNHUD.h"

#include "NNGameMode.generated.h"

/**
 *  Custom Game Mode
 * 
 *  This is meant to handle victory and defeat of any level that might be made for the game.
 *  There probably won't be any other Game Mode or win/loss conditions, hence the generic name.
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_GameMode, Log, All);

UCLASS()
class NOTNOBANOMENT_API ANNGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	ANNGameMode();
	~ANNGameMode();

protected:
	// BeginPlay override in case we need to do some special stuff no matter what level will be loaded.
	virtual void BeginPlay() override;
};
