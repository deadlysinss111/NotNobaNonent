// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NNCollisionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorEnter, AActor*, OtherActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorExit, AActor*, OtherActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorHit, AActor*, OtherActor, const FHitResult&, Hit);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTNOBANOMENT_API UNNCollisionComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere)
    UPrimitiveComponent* CollisionComponent;

public:
    UNNCollisionComponent();

    UPROPERTY(BlueprintAssignable, Category = "Collision")
    FOnActorEnter OnActorEnter;

    UPROPERTY(BlueprintAssignable, Category = "Collision")
    FOnActorExit OnActorExit;

    UPROPERTY(BlueprintAssignable, Category = "Collision")
    FOnActorHit OnActorHit;

    void SetCollisionComponent(UPrimitiveComponent* NewCollisionComponent);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
