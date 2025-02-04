// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/NNEntityInterface.h"

// Add default functionality here for any INNEntityInterface functions that are not pure virtual.

void INNEntityInterface::Start()
{
	//Get the Owner of the component
	AActor* Owner = Cast<AActor>(this);

	// Get all the components of the owner
	TriggerComponent = Owner->FindComponentByClass<UNNTriggerComponent>();
	HealthComponent = Owner->FindComponentByClass<UNNHealthComponent>();


	// Link the events to the functions
	{
		// Set the event to call when an actor enters the trigger
		TriggerComponent->OnActorEnter.AddDynamic(this, &INNEntityInterface::OnActorEnter);
		// Set the event to call when an actor exits the trigger
		TriggerComponent->OnActorExit.AddDynamic(this, &INNEntityInterface::OnActorExit);
	}

	{
		// Set the event to call when the health of the entity changes
		HealthComponent->OnHealthChanged.AddDynamic(this, &INNEntityInterface::OnHealthChanged);
		// Set the event to call when the entity dies
		HealthComponent->OnDeath.AddDynamic(this, &INNEntityInterface::OnDeath);
	}
}

void INNEntityInterface::OnActorEnter(AActor* OtherActor)
{
}

void INNEntityInterface::OnActorExit(AActor* OtherActor)
{
}

void INNEntityInterface::OnHealthChanged(float CurrentHealth)
{
}

void INNEntityInterface::OnDeath()
{
}

