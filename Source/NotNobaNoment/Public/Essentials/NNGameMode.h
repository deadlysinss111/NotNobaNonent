// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// Extra includes
#include "GameFramework/Actor.h"			// Makes Actor handling possible, which is useful immidiately (constructor).
#include "GameFramework/HUD.h"				// Makes HUD handling possible, which is useful immidiately (constructor).
#include "GameFramework/PlayerState.h"		// Used as a default in constructor.
#include "GameFramework/SpectatorPawn.h"	// Used as a default in constructor.
#include "NNGameInstance.h"					// To load levels and use the ELevelName enum.
/* GameMode's GameStates and HUD includes */
#include "NNGameState.h"
#include "NNHUD.h"

#include "NNGameMode.generated.h"


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
public:
	TArray<FString> _LevelsToLoadOnExit;

protected:
	UNNGameInstance* _GameInstance;
	TArray<TMap<FString, bool>> _ExitConds;		// Private from other classes so the setter can have extra logic
	


	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	ANNGameMode();
	~ANNGameMode();

	/* _ExitConds getter & setter */
	const TArray<TMap<FString, bool>>& GetExitConds();
	const TOptional<TMap<FString, bool>> GetExitCondsMap(unsigned int ARGexitCondIndex);
	void SetExitCondsMap(unsigned int ARGexitCondIndex, const TMap<FString, bool>& ARGnewExitCondMap);
	void SetOneExitCond(unsigned int ARGexitCondIndex, FString ARGcondString, bool ARGbool);

	// Try to exit the GameMode given a certain condition map. Called internally when a boolean changes, but also callable by other classes to implement in events.
	void TryExitGameMode(unsigned int ARGexitCondIndex);


protected:
	// Enter and Exit behaviours of the Game Mode
	virtual void BeginPlay() override;
	virtual void ExitGameMode(FString ARGlevelname);

	/* Heplers & Tools */
	bool IsLevelIndexOOB(unsigned int ARGindex);
};
