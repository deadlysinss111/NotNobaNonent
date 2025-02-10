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
	class UInputAction* ForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* RightAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* LookAction;

	//Competences
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* Ability1Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* Ability2Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* Ability3Action;

	//Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UCameraComponent* Camera;

	//CameraBoom
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* CameraBoom;


protected:
	void HandlePlayerInputMove(const FInputActionValue& InputValue);
	void MoveForward(const FInputActionValue& InputValue);
	void MoveRight(const FInputActionValue& InputValue);
	void HandlePlayerDash();
	void HandlePlayerLook(const FInputActionValue& InputValue);
	virtual void HandlePlayerAbility1(const FInputActionValue& InputValue);
	virtual void HandlePlayerAbility2(const FInputActionValue& InputValue);
	virtual void HandlePlayerAbility3(const FInputActionValue& InputValue);

private:
	FTimerHandle DashTimerHandle;
	void ResetDash();

};
