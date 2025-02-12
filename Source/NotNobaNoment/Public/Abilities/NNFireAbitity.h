// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Abilities/NNAbility.h"
#include "Object/NN_ArrowObject.h"

#include "NNFireAbitity.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNFireAbitity : public UNNAbility
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Attack")
    float FireRate = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Attack")
    float Damage = 10.0f;

    FTimerHandle FireTimer;

    bool _isFiring = false;


public:
    virtual void Trigger(KeyState state) override;
    void Fire();

    AActor* _target;
    TSubclassOf<AActor> _BPArrow;
};
