// Fill out your copyright notice in the Description page of Project Settings.


#include "Essentials/NNGameMode.h"


DEFINE_LOG_CATEGORY(NN_GameMode);

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */

// Constru & Destru
ANNGameMode::ANNGameMode()
{
	// Temporary field initializations
	// TODO: Use the correct custom classes when they exist.
	DefaultPawnClass = APawn::StaticClass();
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
	// Intializes fields with default values
	_ELevelOnExit = ELevelName::UNKNOWN;
	_setExitConds = TSet<bool>();

	// AGameModeBase default BeginPlay call.
	Super::BeginPlay();

	// Nothing special yet
	UE_LOG(NN_GameMode, Log, TEXT("Custom GameMode BeginPlay was called ! :D"));
}
void ANNGameMode::TryExitGameMode()
{
	// Checks if all exit conditions were met. If no conditions are founds, assumes exit is allowed at any time.
	if (_setExitConds.Num() == 0) UE_LOG(NN_GameMode, Warning, TEXT("Not exit conditions were found. Is this intentional ? Exiting GameMode..."));
	// UNFINISHED

	// Nothing special yet
	UE_LOG(NN_GameMode, Log, TEXT("Conditions for exiting GameMode were met ! Exiting..."));
}