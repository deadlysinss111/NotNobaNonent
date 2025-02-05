// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// Extra includes
#include "Components/CanvasPanel.h"

#include "NNGenericUserWidget.generated.h"

/**
 *  Custom User Widget
 *
 *  This is meant to put some contraints on the UI when in a level to :
 *   - Ensure no UI element were forgotten
 *   - Add some functionnality on some elements
 */

DECLARE_LOG_CATEGORY_EXTERN(NN_GenericUserWidget, Log, All);

UCLASS()
class NOTNOBANOMENT_API UNNGenericUserWidget : public UUserWidget
{
	GENERATED_BODY()

	/*  ----------    */
   /*  CLASS FIELDS  */
  /*    ----------  */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* PAN_body;



	/*  -----------    */
   /*  CLASS METHODS  */
  /*    -----------  */
public:
	// Constru & Destru
	UNNGenericUserWidget(const FObjectInitializer& ObjectInitializer);
	//virtual void NativeConsruct() override;
};
