// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Interface/NNEntityInterface.h"
#include "Component/NNHealthComponent.h"
#include "Component/NNTriggerComponent.h"
#include "Abilities/NNAbility.h"

#include "NNEntityCharacter.generated.h"

UCLASS()
class NOTNOBANOMENT_API ANNEntityCharacter : public ACharacter, public INNEntityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANNEntityCharacter(); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNTriggerComponent* TriggerComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNAbility* AbilityComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// INNEntityInterface
	UFUNCTION()
	virtual void OnActorEnter(AActor* OtherActor) override;
	UFUNCTION()
	virtual void OnActorExit(AActor* OtherActor) override;

	UFUNCTION()
	virtual void OnHealthChanged(float CurrentHealth) override;
	UFUNCTION()
	virtual void OnDeath() override;


	// Functions 
protected:
	// Movement
	UFUNCTION()
	void Move();
	UFUNCTION()
	void Look();
};
