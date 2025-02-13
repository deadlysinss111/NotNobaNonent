// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"


// Extra includes

#include "NNExitCondsDataAsset.generated.h"

/**
 *  Custom DataAsset class
 * 
 *	This is meant to make TArray storing TMaps compatible with BPs.
 *  That one handles specifically Exit Condition maps.
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_ExitCondDataAsset, Log, All);

UCLASS()
class NOTNOBANOMENT_API UNNExitCondsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	/*  ----------    */
   /*  CLASS FIELDS  */
  /*    ----------  */
public:
	UPROPERTY(EditAnywhere)
	TMap<FString, bool> _condCollection;
};
