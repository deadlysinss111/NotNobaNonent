// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Interface/NNEntityInterface.h"
#include "Component/NNHealthComponent.h"
#include "Component/NNCollisionComponent.h"
#include "Abilities/NNAbility.h"
#include "Abilities/NNAbilitySetDataAsset.h"

#include "NNTurretObject.generated.h"

UCLASS()
class NOTNOBANOMENT_API ANNTurretObject : public APawn, public INNEntityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANNTurretObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNCollisionComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNHealthComponent* HealthComponent;


	UPROPERTY(EditAnywhere)
	UNNAbilitySetDataAsset* _abilitySet;

	UPROPERTY()
	UNNAbility* _ability_1;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* _target;

public:
	// INNEntityInterface

	virtual UNNCollisionComponent* GetCollisionComponent() const override { return CollisionComponent; };
	virtual UNNHealthComponent* GetHealthComponent() const override { return HealthComponent; };

	UFUNCTION()
	virtual void OnActorEnter(AActor* OtherActor) override {};
	UFUNCTION()
	virtual void OnActorExit(AActor* OtherActor) override {};
	UFUNCTION()
	virtual void OnActorHit(AActor* OtherActor, const FHitResult& Hit) override {};

	UFUNCTION()
	virtual void OnHealthChanged(float CurrentHealth) override;
	UFUNCTION()
	virtual void OnDeath() override;


	// End INNEntityInterface
	UFUNCTION(BlueprintCallable)
	void OnEnemyDetected();

	UFUNCTION(BlueprintCallable)
	void LookAtTarget();

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<AActor> ActorBP;

	//Cooldowns for abilities if the turret takes damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldowns")
	float _ability1Cooldown = 0;

};