// Fill out your copyright notice in the Description page of Project Settings.


#include "Essentials/NNGameState.h"


DEFINE_LOG_CATEGORY(NN_GameState);

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */

// Constru & Destru
ANNGameState::ANNGameState()
{
	UWorld* world = GetWorld();

	if (world != nullptr)
	{
		AuthorityGameMode = world->GetAuthGameMode();		// <-- Should always be correct since GameStates are instantiated by a GameMode. This line may be redundant, I'm just making sure.
		GameModeClass = AuthorityGameMode ? AuthorityGameMode->GetClass() : nullptr;
	}
}
ANNGameState::~ANNGameState()
{
	// Nothing yet
}

// BeginPlay override
void ANNGameState::BeginPlay()
{
	Super::BeginPlay();

	// Nothing yet
}