// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

// Extra includes
#include "Blueprint/UserWidget.h"

#include "NNHUD.generated.h"

/**
 *  Custom HUD
 *
 *  This is meant to be the player's HUD and does not include :
 *   - Menus
 *   - Pause screens
 *   - ...
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_HUD, Log, All);

UCLASS()
class NOTNOBANOMENT_API ANNHUD : public AHUD
{
	GENERATED_BODY()

	/*  ----------    */
	/*  CLASS FIELDS  */
	/*    ----------  */
private:
	 UPROPERTY(EditAnywhere, Category = "Code | UserWidget")
	 TSubclassOf<UUserWidget> UserWidget;

	/*  -----------    */
	/*  CLASS METHODS  */
	/*    -----------  */
public:
	// Constru & Destru
	ANNHUD();
	~ANNHUD();

	// Unreal overrides
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
