// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Component/NNHealthComponent.h"
#include "Component/NNCollisionComponent.h"

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

    virtual inline UNNCollisionComponent* GetCollisionComponent() const = 0;
    virtual inline UNNHealthComponent* GetHealthComponent() const = 0;

    // Events 
    //Inlined functions to be overriden by the class that implements the interface
    UFUNCTION()
    virtual inline void OnActorEnter(AActor* OtherActor) {};
    UFUNCTION()
    virtual inline void OnActorExit(AActor* OtherActor) {};
    UFUNCTION()
    virtual inline void OnActorHit(AActor* OtherActor, const FHitResult& Hit) {};

    UFUNCTION()
    virtual inline void OnHealthChanged(float CurrentHealth) {};
    UFUNCTION()
    virtual inline void OnDeath() {};


    template<typename T>
    void InitEventComponent(T* Owner) {
        if (!Owner) return;

		// Get the components
        UNNCollisionComponent* Collision = Owner->GetCollisionComponent();
        UNNHealthComponent* Health = Owner->GetHealthComponent();

		// Bind the events
        if (Collision)
        {
            Collision->OnActorEnter.AddDynamic(Owner, &T::OnActorEnter);
            Collision->OnActorExit.AddDynamic(Owner, &T::OnActorExit);
            Collision->OnActorHit.AddDynamic(Owner, &T::OnActorHit);
        }
        if (Health)
        {
            Health->OnHealthChanged.AddDynamic(Owner, &T::OnHealthChanged);
            Health->OnDeath.AddDynamic(Owner, &T::OnDeath);
        }
    }

};
