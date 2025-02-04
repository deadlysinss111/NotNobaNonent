// Fill out your copyright notice in the Description page of Project Settings.


#include "Essentials/NNGameStatePlaying.h"

DEFINE_LOG_CATEGORY(NN_GameStatePlaying);

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */

// Constru & Destru
ANNGameStatePlaying::ANNGameStatePlaying()
{
	UWorld* world = GetWorld();

	if (world != nullptr)
	{
		AuthorityGameMode = world->GetAuthGameMode();		// <-- Should always be correct since GameStates are instantiated by a GameMode. This line may be redundant, I'm just making sure.
		GameModeClass = AuthorityGameMode ? AuthorityGameMode->GetClass() : nullptr;
	}

	UE_LOG(NN_GameStatePlaying, Log, TEXT("Instantiated GameStatePlaying ! :D"));
}
ANNGameStatePlaying::~ANNGameStatePlaying()
{
	// Nothing yet
}
