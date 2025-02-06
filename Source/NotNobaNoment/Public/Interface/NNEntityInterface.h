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


	// Events
	virtual void OnActorEnter(AActor* OtherActor) {};
	virtual void OnActorExit(AActor* OtherActor) {};
   
	virtual void OnHealthChanged(float CurrentHealth) {};
	virtual void OnDeath() {};

	template<typename T>
		void InitSmth(T* Owner) {
			//Get the trigger component of the owner
			TriggerComponent = Owner->FindComponentByClass<UNNTriggerComponent>();

			if (TriggerComponent)
			{
				TriggerComponent->OnActorEnter.AddDynamic(Owner, &T::OnActorEnter);
				TriggerComponent->OnActorExit.AddDynamic(Owner, &T::OnActorExit);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("The trigger are not valid"));
			}

			//Get the health component of the owner
			HealthComponent = Owner->FindComponentByClass<UNNHealthComponent>();

			if (HealthComponent)
			{
				HealthComponent->OnHealthChanged.AddDynamic(Owner, &T::OnHealthChanged);
				HealthComponent->OnDeath.AddDynamic(Owner, &T::OnDeath);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("The health are not valid"));
			}
			
	}

};
