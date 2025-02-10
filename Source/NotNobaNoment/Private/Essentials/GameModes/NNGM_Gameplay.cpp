// Fill out your copyright notice in the Description page of Project Settings.


#include "Essentials/GameModes/NNGM_Gameplay.h"


DEFINE_LOG_CATEGORY(NNGM_Gameplay);

   /*  -----------    */
  /*  CLASS METHODS  */
 /*    -----------  */

// Constru & Destru
ANNGM_Gameplay::ANNGM_Gameplay()
{
	// TODO: Use the correct custom classes when they exist.
	
	// Temporary field initializations
	DefaultPawnClass = APawn::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();

	// Default fields initializiation
	HUDClass = ANNHUD::StaticClass();
	GameStateClass = ANNGS_Gameplay::StaticClass();
}
ANNGM_Gameplay::~ANNGM_Gameplay()
{
	// Nothing yet
}


// Enter and Exit behaviours of the Game Mode
void ANNGM_Gameplay::BeginPlay()
{
	Super::BeginPlay();

	// Sets the exit conditions maps. An Empty map means an exit attempt will always pass (no constraints).
	_ExitConds.Init(TMap<FString, bool>(), (int)ENNExitCondGameplay::COUNT);
	_ExitConds[(unsigned int) ENNExitCondGameplay::Loss].Add(TEXT("bPlayerDied"), false);
	_ExitConds[(unsigned int) ENNExitCondGameplay::Win].Add(TEXT("bBossBeaten"), false);

	// Sets the levels to load in each scenario. Don't forget a level, otherwise problems !
	_LevelsToLoadOnExit.Init("", (int)ENNExitCondGameplay::COUNT);
	_LevelsToLoadOnExit[(unsigned int) ENNExitCondGameplay::Quit] = "MenuScene";
	_LevelsToLoadOnExit[(unsigned int) ENNExitCondGameplay::Loss] = "MenuScene";
	_LevelsToLoadOnExit[(unsigned int) ENNExitCondGameplay::Win] = "MenuScene";
}