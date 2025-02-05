// Fill out your copyright notice in the Description page of Project Settings.

#include "Essentials/NNGameMode.h"
#include "Character/NNPlayerCharacter.h"
DEFINE_LOG_CATEGORY(NN_GameMode);

/*  -----------    */
/*  CLASS METHODS  */
/*    -----------  */

// Constru & Destru
ANNGameMode::ANNGameMode()
{
	// Temporary field initializations
	// TODO: Use the correct custom classes when they exist.
	DefaultPawnClass = ANNPlayerCharacter::StaticClass();
	DefaultPlayerName = FText::FromString("Player");
	PlayerControllerClass = APlayerController::StaticClass();

	// Default fields initializiation
	HUDClass = ANNHUD::StaticClass();
	GameStateClass = ANNGameStatePlaying::StaticClass();

	// Set to None since those will probably remain unused
	PlayerStateClass = nullptr;
	SpectatorClass = nullptr;
}
ANNGameMode::~ANNGameMode()
{
	// Nothing yet
}

// BeginPlay override in case we need to do some special stuff no matter what level will be loaded.
void ANNGameMode::BeginPlay()
{
	// AGameModeBase default BeginPlay call.
	Super::BeginPlay();

	// Nothing special yet
	UE_LOG(NN_GameMode, Log, TEXT("Custom GameMode BeginPlay was called ! :D"));
}