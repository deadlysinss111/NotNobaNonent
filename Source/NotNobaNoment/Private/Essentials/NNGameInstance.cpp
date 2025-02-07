// Fill out your copyright notice in the Description page of Project Settings.


#include "Essentials/NNGameInstance.h"


DEFINE_LOG_CATEGORY(NN_GameInstance);

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */

// Constru & Destru
UNNGameInstance::UNNGameInstance(const FObjectInitializer& ARG_ObjectInitializer)
	: Super(ARG_ObjectInitializer)
{
	// Nothing yet
	UE_LOG(NN_GameInstance, Log, TEXT("Constructed UNNGameInstance ! :D"));
}
UNNGameInstance::~UNNGameInstance()
{
	// Nothing yet
}


// BeginPlay override to become aware of the levels available for the game.
void UNNGameInstance::Init()
{
	Super::Init();

	// Retrieves the AssetRegistryModule to query it later.
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	// Prepares the query through a receiveing TArray and a filter FARFilter.
	TArray<FAssetData> AssetDataQueryResult;
	FARFilter RecurWorldFilter;
	RecurWorldFilter.PackagePaths.Add("/Game/Levels");	// After "Game/", starts from the folder "Content".
	RecurWorldFilter.ClassPaths.Add(FTopLevelAssetPath(FName("/Script/Engine"), FName("World")));	// wtf is that, man...
	RecurWorldFilter.bRecursivePaths = true;

	// Fires the query, and stores the results in _arrLevels.
	AssetRegistryModule.Get().GetAssets(RecurWorldFilter, AssetDataQueryResult);
	for (const FAssetData& Asset : AssetDataQueryResult)
	{
		_arrLevels.Add(Asset.AssetName);
		UE_LOG(NN_GameInstance, Log, TEXT("Found and stored level %s !"), *Asset.AssetName.ToString());
	}
}



/* Level loaders */
void UNNGameInstance::LoadLevel(unsigned int ARGindex)
{
	// Loads the level if the index is a valid one.
	if (!IsLevelIndexOOB(ARGindex))
		UGameplayStatics::OpenLevel(GetWorld()/*<-- Context arg*/, _arrLevels[ARGindex]);
}
void UNNGameInstance::LoadLevel(ELevelName ARGeLevelName)
{
	unsigned int index = (unsigned int)ARGeLevelName;

	// Loads the level if the index is a valid one.
	if (! IsLevelIndexOOB(index))
		UGameplayStatics::OpenLevel(GetWorld()/*<-- Context arg*/, _arrLevels[index]);
}



/* Helpers & Tools */
bool UNNGameInstance::IsLevelIndexOOB(unsigned int ARGindex)
{
	// Invalid index scenario
	if (ARGindex >= (unsigned int)_arrLevels.Num())
	{
		UE_LOG(NN_GameInstance, Error, TEXT("Couldn't load level index %d : OUT OF BOUNDS (valid indexes : [0-%d])"), ARGindex, _arrLevels.Num() - 1);
		return true;
	}

	// Valid index scenario
	else return false;
}