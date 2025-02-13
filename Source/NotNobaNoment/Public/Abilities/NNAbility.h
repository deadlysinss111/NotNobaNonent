// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "NNAbility.generated.h"

UENUM(/*BlueprintType*/)
enum class KeyState {
	Start = 0,
	Hold,
	End,
	None = -1,
};


UCLASS(BlueprintType)
class NOTNOBANOMENT_API UNNAbility : public UObject
{
	GENERATED_BODY()


protected:
	UPROPERTY()
	APawn* _owner;

public:
	UFUNCTION()
	virtual void Init(APawn* owner);

	UFUNCTION(BlueprintCallable)
	virtual void Trigger(KeyState state = KeyState::None) {};
	
};
