// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Interface/NNEntityInterface.h"
#include "Component/NNHealthComponent.h"
#include "Component/NNCollisionComponent.h"
#include "Abilities/NNAbility.h"
#include <InputAction.h>

#include "NNEntityCharacter.generated.h"

UCLASS()
class NOTNOBANOMENT_API ANNEntityCharacter : public ACharacter, public INNEntityInterface
{
	GENERATED_BODY()

public:
	ANNEntityCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNCollisionComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNAbility* AbilityComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// INNEntityInterface

	UFUNCTION(BlueprintCallable, Category = "Entity")
	virtual UNNCollisionComponent* GetCollisionComponent() const override { return CollisionComponent; };
	UFUNCTION(BlueprintCallable, Category = "Entity")
	virtual UNNHealthComponent* GetHealthComponent() const override { return HealthComponent; };

	UFUNCTION(BlueprintCallable, Category = "Entity")
	virtual void OnActorEnter(AActor* OtherActor) override {};
	UFUNCTION(BlueprintCallable, Category = "Entity")
	virtual void OnActorExit(AActor* OtherActor) override {};
	UFUNCTION(BlueprintCallable, Category = "Entity")
	virtual void OnActorHit(AActor* OtherActor, const FHitResult& Hit) override {};

	UFUNCTION(BlueprintCallable, Category = "Entity")
	virtual void OnHealthChanged(float CurrentHealth) override;
	UFUNCTION(BlueprintCallable, Category = "Entity")
	virtual void OnDeath() override { Destroy(); };
};
