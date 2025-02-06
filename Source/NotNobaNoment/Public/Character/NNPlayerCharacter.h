// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NNEntityCharacter.h"
#include "Abilities/NNAbilitySetDataAsset.h"
#include "Abilities/NNAbility.h"
#include "NNPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API ANNPlayerCharacter : public ANNEntityCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANNPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	UNNAbilitySetDataAsset* _abilitySet;

	UPROPERTY()
	UNNAbility* _attack;

	UPROPERTY()
	UNNAbility* _ability_1;

	UPROPERTY()
	UNNAbility* _ability_2;

	//Input System
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputMappingContext* InputMappingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UCameraComponent* Camera;

private:
	UFUNCTION()
	void TriggerAttack();

	UFUNCTION()
	void TriggerAbility_1();

	UFUNCTION()
	void TriggerAbility_2();
};
