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
