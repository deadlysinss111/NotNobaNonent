// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/NN_ArrowObject.h"

// Sets default values
ANN_ArrowObject::ANN_ArrowObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UNNCollisionComponent>(TEXT("CollisionComponent"));

	// Init the event component
	InitEventComponent<ANN_ArrowObject>(this);
}

// Called when the game starts or when spawned
void ANN_ArrowObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANN_ArrowObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(GetActorForwardVector(), _speed);

	// After 5 seconds, destroy the arrow
	_lifeTime += DeltaTime;
	if (_lifeTime >= 5.0f)
	{
		Destroy();
	}
}

void ANN_ArrowObject::Move(FVector direction, float speed)
{
	SetActorLocation(GetActorLocation() + direction * speed);
}

void ANN_ArrowObject::OnActorEnter(AActor* OtherActor)
{	
	// other actor have a health component
	if (OtherActor->Implements<UNNEntityInterface>())
	{
		INNEntityInterface* entity = Cast<INNEntityInterface>(OtherActor);
		if (entity)
		{

			entity->GetHealthComponent()->ApplyDamage(_dammage);
		}
	}

	// destroy the arrow
	Destroy();
}

