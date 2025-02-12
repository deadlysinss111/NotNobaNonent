// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/NNAbility.h"
#include "NNDagger.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "NNThrowDaggerAbility.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FActionToTrigger, KeyState, state);

#define SPLINE_SIZE		(80)

/**
 * 
 */
UCLASS()
class NOTNOBANOMENT_API UNNThrowDaggerAbility : public UNNAbility
{
	GENERATED_BODY()

private:
	FActionToTrigger _currentAction;

	UPROPERTY(EditAnywhere)
	ANNDagger* _dagger;
	
public:
	void Init(APawn* owner) override;
	void Trigger(KeyState state) override;

	UFUNCTION()
	void Throw(KeyState state);
	UFUNCTION()
	void Jump(KeyState state);
	UFUNCTION()
	void RenderCurve(KeyState state);

	void ResetCurve();

private:
	UPROPERTY()
	UStaticMesh* _mesh;
	UPROPERTY()
	UMaterialInterface* _material;

private:
	UPROPERTY()
	USplineComponent* _spline;
	UPROPERTY()
	TArray<USplineMeshComponent*> _splineMeshes;
};
