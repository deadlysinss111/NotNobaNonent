// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Extra includes
#include "AssetRegistry/AssetRegistryModule.h"	// To find all level in the project
#include "Kismet/GameplayStatics.h"				// To load levels

#include "NNGameInstance.generated.h"


/**
 *  Custom Game Instance
 * 
 *  This is meant to hold :
 *   - Settings (eg. Volume)
 *   - Inventory & Stats
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_GameInstance, Log, All);

UCLASS()
class NOTNOBANOMENT_API UNNGameInstance : public UGameInstance
{
	GENERATED_BODY()

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	UNNGameInstance(const FObjectInitializer& ARG_ObjectInitializer);
	~UNNGameInstance();

	// BeginPlay override to become aware of the levels available for the game.
	virtual void Init() override;

	/* Level loaders */
	void LoadLevel(FString ARGlevelName);
};
