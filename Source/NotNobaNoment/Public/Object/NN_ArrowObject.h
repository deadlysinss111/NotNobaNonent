// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Component/NNCollisionComponent.h"
#include "Interface/NNEntityInterface.h"

#include "NN_ArrowObject.generated.h"

UCLASS()
class NOTNOBANOMENT_API ANN_ArrowObject : public AActor, public INNEntityInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANN_ArrowObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Interface functions
	void Move(FVector direction, float speed);

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UNNCollisionComponent* CollisionComponent;
	
	float _lifeTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arrow")
	float _speed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Arrow")
	float _dammage = 10.f;

	// Interface functions
	virtual UNNCollisionComponent* GetCollisionComponent() const override { return CollisionComponent; }
	virtual UNNHealthComponent* GetHealthComponent() const override { return nullptr; }

	// Events
	virtual void OnActorEnter(AActor* OtherActor) override;
	virtual void OnActorExit(AActor* OtherActor) override {};
	virtual void OnActorHit(AActor* OtherActor, const FHitResult& Hit) override {};

	virtual void OnHealthChanged(float CurrentHealth) override {};
	virtual void OnDeath() override {};
};
