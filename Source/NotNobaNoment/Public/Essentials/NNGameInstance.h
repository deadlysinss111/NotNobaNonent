// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Extra includes

#include "NNGameInstance.generated.h"



/**
 *  Custom Game Instance
 * 
 *  This is meant to hold :
 *   - Settings (eg. Volume)
 *   - Inventory & Stats
 */

DECLARE_LOG_CATEGORY_EXTERN(GameInstance, Log, All);

UCLASS()
class NOTNOBANOMENT_API UNNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	/*  -----------  */
	/* CLASS METHODS */
	/*  -----------  */
public:
	// Constru & Destru
	UNNGameInstance(const FObjectInitializer& ARG_ObjectInitializer);
	~UNNGameInstance();
};
