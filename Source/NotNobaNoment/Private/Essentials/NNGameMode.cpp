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
	GameStateClass = ANNGameState::StaticClass();

	// Set to None since those will probably remain unused
	PlayerStateClass = nullptr;
	SpectatorClass = nullptr;
}
ANNGameMode::~ANNGameMode()
{
	// Nothing yet
}



// Enter and Exit behaviours of the Game Mode
void ANNGameMode::BeginPlay()
{
	// Intializes fields.
	_ExitConds = TArray<TMap<FString, bool>>();
	_ExitConds.Add(TMap<FString, bool>());		// Empty bool map for Quit conditions (index 0)
	_ExitConds.Add(TMap<FString, bool>());		// Empty bool map for Loss conditions (index 1)
	_ExitConds.Add(TMap<FString, bool>());		// Empty bool map for Win conditions (index 2)

	// Sets fields default values.
	_ELevelOnExit = ENNLevel::UNKNOWN;
	_ExitConds[(unsigned int) ENNExitCond::Quit].Add(TEXT("bPlayerWannaQuit"), false);
	_ExitConds[(unsigned int) ENNExitCond::Loss].Add(TEXT("bPlayerDied"), false);


	// AGameModeBase default BeginPlay call.
	Super::BeginPlay();
}
void ANNGameMode::ExitGameMode()
{
	// Nothing special yet
	UE_LOG(NN_GameMode, Log, TEXT("Conditions for exiting GameMode were met ! Exiting..."));
}



/* _ExitConds getter & setter */
const TArray<TMap<FString, bool>>& ANNGameMode::GetExitConds()
{
	return _ExitConds;
}
const TOptional<TMap<FString, bool>> ANNGameMode::GetExitCondsMap(ENNExitCond ARGeExitCond)
{
	if (!IsLevelIndexOOB(ARGeExitCond))
		return _ExitConds[(int) ARGeExitCond];	// This returns a valid TOptional since a value is retuned AND TOptional has an implicit conversion :3 (TL;DR magic QoL).
	else
		return TOptional<TMap<FString, bool>>();	// This returns an invalid TOptional since no value is passed in its constructor.
}
void ANNGameMode::SetExitCondsMap(ENNExitCond ARGeExitCond, const TMap<FString, bool>& ARGnewExitCondMap)
{
	// Sets the new values
	_ExitConds[(int) ARGeExitCond] = ARGnewExitCondMap;

	// Try to exit the GameMode
	TryExitGameMode(ARGeExitCond);
}
void ANNGameMode::SetOneExitCond(ENNExitCond ARGeExitCond, FString ARGcondString, bool ARGbool)
{
	// Sets the new value
	bool* value = _ExitConds[(int)ARGeExitCond].Find(ARGcondString);
	if (value != nullptr) *value = ARGbool;

	// Try to exit the GameMode
	TryExitGameMode(ARGeExitCond);
}



/* Helpers & Tools */
bool ANNGameMode::IsLevelIndexOOB(unsigned int ARGindex)
{
	// Invalid index scenario
	if (ARGindex >= (unsigned int)_ExitConds.Num())
	{
		UE_LOG(NN_GameMode, Error, TEXT("Couldn't load level index %d : OUT OF BOUNDS (valid indexes : [0-%d])"), ARGindex, _ExitConds.Num() - 1);
		return true;
	}

	// Valid index scenario
	else return false;
}
bool ANNGameMode::IsLevelIndexOOB(ENNExitCond ARGeExitCond)
{
	// Promotes the enum type into a uint type
	unsigned int index = (unsigned int)ARGeExitCond;

	return IsLevelIndexOOB(index);
}
void ANNGameMode::TryExitGameMode(ENNExitCond ARGeExitCond)
{
	// Retrieves what we're checking
	TMap<FString, bool> mapCurChecked = _ExitConds[(int) ARGeExitCond];
	TArray<FString> arrKeysOfCurChecked;
	mapCurChecked.GetKeys(arrKeysOfCurChecked);

	// By default, assume we should call ExitGameMode().
	bool bShouldCallExitGameMode = true;
	for (const FString& key : arrKeysOfCurChecked)
	{
		// If an exit condition contradicts the above assumption, cancel the ExitGameMode() call.
		if (mapCurChecked[key] == false)
		{
			bShouldCallExitGameMode = false;
			break;
		}
	}
	if (bShouldCallExitGameMode)
	{
		UE_LOG(NN_GameMode, Log, TEXT("ExitCond map %d allowed an exit ! Calling ExitGameMode..."), (int)ARGeExitCond);
		ExitGameMode();
	}
}