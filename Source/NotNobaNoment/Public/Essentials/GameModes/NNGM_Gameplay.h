// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Essentials/NNGameMode.h"

// Extra includes
/* GameMode's GameStates and HUD includes */
#include "../GameStates/NNGS_Gameplay.h"
// TODO: Make an HUD for this class

#include "NNGM_Gameplay.generated.h"


// Abstraction for easier exit conditions index access. This is not inside of the class since GameModes' GameStates could need that.
UENUM()
enum class ENNExitCondGameplay
{
	UNKNOWN = -1,

	Quit = 0,
	Loss,
	Win,

	COUNT UMETA(Hidden)
};

/**
 *  Gameplay Game Mode
 *
 *  This is a Game Mode meant to be used when in a level playing the game.
 *  That implies mostly the enum used as index for the exit conds and what you'll likely find in those exit conds.
 */

DECLARE_LOG_CATEGORY_EXTERN(NNGM_Gameplay, Log, All);

UCLASS()
class NOTNOBANOMENT_API ANNGM_Gameplay : public ANNGameMode
{
	GENERATED_BODY()
	
	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	ANNGM_Gameplay();
	~ANNGM_Gameplay();


protected:
	// Enter behaviour of the Game Mode
	virtual void BeginPlay() override;
};
