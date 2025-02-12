//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "NNHitComponent.generated.h"
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorHit, AActor*, HittingActor);
//
//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
//class NOTNOBANOMENT_API UNNHitComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:	
//	// Sets default values for this component's properties
//	UNNHitComponent();
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:
//	//Generique collision component
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyGenerique/Collision")
//	UPrimitiveComponent* CollisionComponent;
//
//
//	UPROPERTY(BlueprintAssignable, Category = "MyGenerique/Collision")
//	FOnActorOverlap OnActorEnter;
//
//	UPROPERTY(BlueprintAssignable, Category = "MyGenerique/Collision")
//	FOnActorOverlap OnActorExit;
//
//
//	//Chanage the collision component
//	UFUNCTION(BlueprintCallable, Category = "MyGenerique/Collision")
//	void setCollisionComponent(UPrimitiveComponent* NewCollisionComponent);
//
//	UFUNCTION()
//	void HandleHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
//
//		
//};
