// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Component/NNHealthComponent.h"
#include "Component/NNTriggerComponent.h"

#include "NNEntityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNNEntityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NOTNOBANOMENT_API INNEntityInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UNNTriggerComponent* TriggerComponent;
	UNNHealthComponent* HealthComponent;
	// Other components


	// Call this function to link the events to the functions on the BeginPlay of the owner
	UFUNCTION()
	virtual void Start();


	// Events
	UFUNCTION()
	virtual void OnActorEnter(AActor* OtherActor) = 0;
	UFUNCTION()
	virtual void OnActorExit(AActor* OtherActor) = 0;

	UFUNCTION()
	virtual void OnHealthChanged(float CurrentHealth) = 0;
	UFUNCTION()
	virtual void OnDeath();

	// Other events

};
