// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Component/NNHealthComponent.h"
#include "NNGlassCeilling.generated.h"

UCLASS()
class NOTNOBANOMENT_API ANNGlassCeilling : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANNGlassCeilling();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UNNHealthComponent* HealthComponent;

private:
	UFUNCTION()
	virtual inline void OnHealthChanged(float CurrentHealth) {};
	UFUNCTION()
	virtual inline void OnDeath();

};
