// Fill out your copyright notice in the Description page of Project Settings.


#include "Essentials/NNHUD.h"

DEFINE_LOG_CATEGORY(NN_HUD);

	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */

// Constru & Destru
ANNHUD::ANNHUD()
{
	// Nothing. Apparently, the Canvas field is set automatically somehow.
	// Might be useful to add some code for debugging later here with `#if WITH_EDITOR`
}
ANNHUD::~ANNHUD()
{
	// Nothing yet
}


// Unreal overrides
void ANNHUD::DrawHUD()
{
	// Nothing yet
}
void ANNHUD::BeginPlay()
{
	// Nothing yet
}
void ANNHUD::Tick(float DeltaSeconds)
{
	// Nothing yet
}