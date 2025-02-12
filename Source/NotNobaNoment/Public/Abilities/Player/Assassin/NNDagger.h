// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/NNEntityInterface.h"
#include "Character/NNPlayerCharacter.h"
#include "NiagaraComponent.h"
#include <functional>
#include "NNDagger.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FStateAction, AActor*, OtherActor);


UCLASS()
class NOTNOBANOMENT_API ANNDagger : public AActor, public INNEntityInterface
{
	GENERATED_BODY()

public:
	enum class DaggerState
	{
		Handed = 0,
		Hitting,
		Flying,
		Grounded,
	};
	
private:
	UNiagaraSystem* _pickupAttackFX;


public:	
	ANNDagger();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNNCollisionComponent* TriggerComponent;

public:
	DaggerState _currentState;
	//void(*_currentStateAction)(AActor* OtherActor);
	UPROPERTY()
	FStateAction _currentStateAction;
	
	//std::function<void(AActor*)> _currentStateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arrow")
	float _dammage = 10.f;

private:
	UPROPERTY();
	TArray<AActor*> _ObjectsHitOnTheFly;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnActorEnter(AActor* OtherActor) override;
	UFUNCTION()
	virtual void OnActorExit(AActor* OtherActor) override {};
	UFUNCTION()
	virtual void OnActorHit(AActor* OtherActor, const FHitResult& Hit) override;

	UFUNCTION()
	virtual void OnHealthChanged(float CurrentHealth) override {};
	UFUNCTION()
	virtual void OnDeath() override {};

	UFUNCTION()
	inline UNNCollisionComponent* GetCollisionComponent() const override { return TriggerComponent; };
	UFUNCTION()
	inline UNNHealthComponent* GetHealthComponent() const override { return nullptr; };


public:
	void ChangeState(DaggerState newState);

	UFUNCTION(BlueprintCallable)
	void SetBackToHanded();

	UFUNCTION()
	void HandedOverlapAction(AActor* OtherActor);
	UFUNCTION()
	void HittingOverlapAction(AActor* OtherActor);
	UFUNCTION()
	void FlyingOverlapAction(AActor* OtherActor);
	UFUNCTION()
	void GroundedOverlapAction(AActor* OtherActor);

	void Slash();
	void PickupAttack(ANNPlayerCharacter* OtherActor);
};
