// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NNEntityCharacter.h"

// Extra includes
/* MOVED IN ENEITTY */
//#include "Abilities/NNAbilitySetDataAsset.h"
//#include "Abilities/NNAbility.h"

//#include "Interfaces/GeneriqueTeamAgentInterface.h"

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
	// Uncomment and adapt if UserWidget for the player becomes a C++ class
	//UPROPERTY(BlueprintReadWrite)
	//UUserWidget* _DesignatedUserWidget;

	// Used in UserWidget (BP version)
	UPROPERTY(BlueprintReadOnly) float ability1RemainingCooldown;
	UPROPERTY(BlueprintReadOnly) float ability2RemainingCooldown;
	UPROPERTY(BlueprintReadOnly) float ability3RemainingCooldown;
	UPROPERTY(BlueprintReadOnly) bool bIsAbility1UseAllowed;
	UPROPERTY(BlueprintReadOnly) bool bIsAbility2UseAllowed;
	UPROPERTY(BlueprintReadOnly) bool bIsAbility3UseAllowed;

	// Special boolean to change an icon in UserWidget (BP version)
	UPROPERTY(BlueprintReadOnly) bool bIsDaggerInHand;

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
	UPROPERTY(BlueprintReadWrite, Category = "Entity")
	float ability1Cooldown;
	FTimerHandle Ability1Authoriser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* Ability2Action;
	UPROPERTY(BlueprintReadWrite, Category = "Entity")
	float ability2Cooldown;
	FTimerHandle Ability2Authoriser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* Ability3Action;
	UPROPERTY(BlueprintReadWrite, Category = "Entity")
	float ability3Cooldown;
	FTimerHandle Ability3Authoriser;

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

	void StartPlayerAbility1(const FInputActionValue& InputValue);
	void HoldPlayerAbility1(const FInputActionValue& InputValue);
	void EndPlayerAbility1(const FInputActionValue& InputValue);
	void StartPlayerAbility2(const FInputActionValue& InputValue);
	void HoldPlayerAbility2(const FInputActionValue& InputValue);
	void EndPlayerAbility2(const FInputActionValue& InputValue);
	void StartPlayerAbility3(const FInputActionValue& InputValue);
	void HoldPlayerAbility3(const FInputActionValue& InputValue);
	void EndPlayerAbility3(const FInputActionValue& InputValue);

	void SetAbiltity1UseAllowed();
	void SetAbiltity2UseAllowed();
	void SetAbiltity3UseAllowed();


private:
	FTimerHandle DashTimerHandle;
	void ResetDash();

};
