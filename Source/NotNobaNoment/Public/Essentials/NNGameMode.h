// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// Extra includes
#include "GameFramework/Actor.h"	// Makes Actor handling possible, which is useful immidiately (constructor).
#include "GameFramework/HUD.h"		// Makes HUD handling possible, which is useful immidiately (constructor). Not included above, for some reason.
#include "NNGameInstance.h"			// To load levels and use the ELevelName enum.
/* GameMode's GameStates and HUD includes */
#include "NNGameStatePlaying.h"
#include "NNHUD.h"

#include "NNGameMode.generated.h"

// TODO: Move this comment block over to the GameMode concerned
/**
 *  Custom Game Mode
 * 
 *  This is meant to handle victory and defeat of any level that might be made for the game.
 *  There probably won't be any other Game Mode or win/loss conditions, hence the generic name.
 */

/**
 *  Custom Game Mode
 * 
 *  This is meant to be a generic Game Mode for this game specifically.
 *  It features fields and methods to "exit" the Game Mode and load another level.
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_GameMode, Log, All);

UCLASS()
class NOTNOBANOMENT_API ANNGameMode : public AGameModeBase
{
	GENERATED_BODY()

	/*  ----------    */
   /*  CLASS FIELDS  */
  /*    ----------  */
	ELevelName _ELevelOnExit;
	TSet<bool> _setExitConds;
	


	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	ANNGameMode();
	~ANNGameMode();

protected:
	// Enter and Exit behaviours of the Game Mode
	virtual void BeginPlay() override;
	virtual void TryExitGameMode();
};
