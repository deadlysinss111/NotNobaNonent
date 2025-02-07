// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NNEntityCharacter.h"
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

	//Input System
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputMappingContext* InputMappingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UInputAction* LookAction;

	//Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	class UCameraComponent* Camera;


protected:
	void HandlePlayerInputMove(const FInputActionValue& InputValue);;
	void HandlePlayerLook(const FInputActionValue& InputValue);
};
