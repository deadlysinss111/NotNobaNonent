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

	/*
	 * 
	 *  This code became useless because levels are found in such an order that blablabla this class is naked now :(
	 * 
	 * // Retrieves the AssetRegistryModule to query it later.
	 * FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	 * 
	 * // Prepares the query through a receiveing TArray and a filter FARFilter.
	 * TArray<FAssetData> AssetDataQueryResult;
	 * FARFilter RecurWorldFilter;
	 * RecurWorldFilter.PackagePaths.Add("/Game/Levels");	// After "Game/", starts from the folder "Content".
	 * RecurWorldFilter.ClassPaths.Add(FTopLevelAssetPath(FName("/Script/Engine"), FName("World")));	// wtf is that, man...
	 * RecurWorldFilter.bRecursivePaths = true;
	 * 
	 * // Fires the query, and stores the results in _arrLevels.
	 * AssetRegistryModule.Get().GetAssets(RecurWorldFilter, AssetDataQueryResult);
	 * for (const FAssetData& Asset : AssetDataQueryResult)
	 * {
	 *    _arrLevels.Add(Asset.AssetName);
	 * 	  UE_LOG(NN_GameInstance, Log, TEXT("Found and stored level %s !"), *Asset.AssetName.ToString());
	 * }
	 */
}



/* Level loaders */
void UNNGameInstance::LoadLevel(FString ARGlevelName)
{
	UWorld* curWorld = GetWorld();
	if (curWorld == nullptr)
	{
		UE_LOG(NN_GameInstance, Error, TEXT("LoadLevel says : GetWorld() returned nullptr somehow ! Can't proceed, retuning..."));
		return;
	}
	else UGameplayStatics::OpenLevel(curWorld/*<-- Context arg*/, FName(*ARGlevelName));
}