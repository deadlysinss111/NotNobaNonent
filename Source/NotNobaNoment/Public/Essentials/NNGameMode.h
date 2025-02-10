// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// Extra includes
#include "GameFramework/Actor.h"	// Makes Actor handling possible, which is useful immidiately (constructor).
#include "GameFramework/HUD.h"		// Makes HUD handling possible, which is useful immidiately (constructor). Not included above, for some reason.
#include "NNGameInstance.h"			// To load levels and use the ELevelName enum.
/* GameMode's GameStates and HUD includes */
#include "NNGameState.h"
#include "NNHUD.h"

#include "NNGameMode.generated.h"



// Abstraction for easier exit conditions index access. Generic.
UENUM()
enum class ENNExitCond
{
	UNKNOWN = -1,

	Quit = 0,
	Loss,
	Win,

	COUNT UMETA(Hidden)
};

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
	ENNLevel _ELevelOnExit;

protected:
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
	const TOptional<TMap<FString, bool>> GetExitCondsMap(ENNExitCond ARGeExitCond);
	void SetExitCondsMap(ENNExitCond ARGeExitCond, const TMap<FString, bool>& ARGnewExitCondMap);
	void SetOneExitCond(ENNExitCond ARGeExitCond, FString ARGcondString, bool ARGbool);

	// Try to exit the GameMode given a certain condition map. Called internally when a boolean changes, but also callable by other classes to implement in events.
	void TryExitGameMode(ENNExitCond ARGeExitCond);


protected:
	// Enter and Exit behaviours of the Game Mode
	virtual void BeginPlay() override;
	// Exit behaviour of the Game Mode
	virtual void ExitGameMode();

	/* Heplers & Tools */
	bool IsLevelIndexOOB(unsigned int ARGindex);
	bool IsLevelIndexOOB(ENNExitCond ARGeExitCond);
};
