// Fill out your copyright notice in the Description page of Project Settings.


#include "Essentials/GameStates/NNGS_Gameplay.h"

// .cpp exclusive includes
#include "../../../Public/Essentials/GameModes/NNGM_Gameplay.h"


DEFINE_LOG_CATEGORY(NNGS_Gameplay);

   /*  -----------    */
  /*  CLASS METHODS  */
 /*    -----------  */

// Constru & Destru
ANNGS_Gameplay::ANNGS_Gameplay()
{
	UE_LOG(NN_GameState, Log, TEXT("Instantiated GameState_Gameplay ! :D"));
}
ANNGS_Gameplay::~ANNGS_Gameplay()
{
	// Nothing yet
}

// BeginPlay override
void ANNGS_Gameplay::BeginPlay()
{
	Cast<ANNGM_Gameplay>(AuthorityGameMode)->TryExitGameMode((unsigned int) ENNExitCondGameplay::Quit);
}