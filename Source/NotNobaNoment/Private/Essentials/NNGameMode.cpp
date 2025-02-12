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
	PlayerControllerClass = APlayerController::StaticClass();

	// Default fields initializiation
	HUDClass = ANNHUD::StaticClass();
	GameStateClass = ANNGameState::StaticClass();

	// Set to default Unreal stuff since those will probably remain unused
	DefaultPlayerName = FText::FromString("Player");
	PlayerStateClass = APlayerState::StaticClass();
	SpectatorClass = ASpectatorPawn::StaticClass();
}
ANNGameMode::~ANNGameMode()
{
	// Nothing yet
}



// Enter and Exit behaviours of the Game Mode
void ANNGameMode::BeginPlay()
{
	// AGameModeBase default BeginPlay call.
	Super::BeginPlay();

	// Intializes fields.
	_ExitConds = TArray<TMap<FString, bool>>();
	_LevelsToLoadOnExit = TArray<FString>();
	_GameInstance = (UNNGameInstance*) UGameplayStatics::GetGameInstance(GetWorld());
}
void ANNGameMode::ExitGameMode(FString ARGlevelname)
{
	UE_LOG(NN_GameMode, Log, TEXT("Conditions for exiting GameMode were met ! Loading level %s..."), *ARGlevelname);
	_GameInstance->LoadLevel(ARGlevelname);
}



/* _ExitConds getter & setter */
const TArray<TMap<FString, bool>>& ANNGameMode::GetExitConds()
{
	return _ExitConds;
}
const TOptional<TMap<FString, bool>> ANNGameMode::GetExitCondsMap(unsigned int ARGexitCondIndex)
{
	if (!IsLevelIndexOOB(ARGexitCondIndex))
		return _ExitConds[ARGexitCondIndex];	// This returns a valid TOptional since a value is retuned AND TOptional has an implicit conversion :3 (TL;DR magic QoL).
	else
		return TOptional<TMap<FString, bool>>();	// This returns an invalid TOptional since no value is passed in its constructor.
}
void ANNGameMode::SetExitCondsMap(unsigned int ARGexitCondIndex, const TMap<FString, bool>& ARGnewExitCondMap)
{
	// Sets the new values
	_ExitConds[ARGexitCondIndex] = ARGnewExitCondMap;

	// Try to exit the GameMode
	TryExitGameMode(ARGexitCondIndex);
}
void ANNGameMode::SetOneExitCond(unsigned int ARGexitCondIndex, FString ARGcondString, bool ARGbool)
{
	// Sets the new value
	bool* value = _ExitConds[ARGexitCondIndex].Find(ARGcondString);
	if (value != nullptr) *value = ARGbool;

	// Try to exit the GameMode
	TryExitGameMode(ARGexitCondIndex);
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
void ANNGameMode::TryExitGameMode(unsigned int ARGexitCondIndex)
{
	// Retrieves what we're checking
	TMap<FString, bool> mapCurChecked = _ExitConds[ARGexitCondIndex];
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
		UE_LOG(NN_GameMode, Log, TEXT("ExitCond map %d allowed an exit ! Calling ExitGameMode..."), ARGexitCondIndex);
		ExitGameMode(_LevelsToLoadOnExit[ARGexitCondIndex]);
	}
}