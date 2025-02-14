// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/NNTurretObject.h"
#include <Abilities/NNFireAbitity.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values

ANNTurretObject::ANNTurretObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create component
	CollisionComponent = CreateDefaultSubobject<UNNCollisionComponent>(TEXT("CollisionComponent"));
	HealthComponent = CreateDefaultSubobject<UNNHealthComponent>(TEXT("HealthComponent"));

	// Init the event component
	InitEventComponent<ANNTurretObject>(this);
}

// Called when the game starts or when spawned
void ANNTurretObject::BeginPlay()
{
	Super::BeginPlay();

	if (_abilitySet != NULL) {

		_ability_1 = NewObject<UNNAbility>(this, _abilitySet->_ability_1);
		_ability_1->Init(this);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("the ability set is null"));

	if(!ActorBP)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("the projectil actor is null"));
	}
}

// Called every frame
void ANNTurretObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_ability1Cooldown > 0)
	{
		_ability1Cooldown -= DeltaTime;
	}

	if (_target)
	{
		LookAtTarget();
	}
}

void ANNTurretObject::OnHealthChanged(float CurrentHealth)
{
	_ability1Cooldown = 2;
}

void ANNTurretObject::OnDeath()
{
	Destroy();
}

void ANNTurretObject::OnEnemyDetected()
{
	if (_ability_1 && _ability1Cooldown == 0)
	{	
		//Turn the turret to the target
		//TODO replace GetActorLocation() by the location of the top

		UNNFireAbitity* abilityTemp = Cast<UNNFireAbitity>(_ability_1);
		abilityTemp->_target = _target;
		abilityTemp->_BPArrow = ActorBP;
		_ability_1->Trigger(KeyState::None);
	}
	
}

void ANNTurretObject::LookAtTarget()
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _target->GetActorLocation());
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f); // 5.0f est la vitesse de rotation
	SetActorRotation(SmoothRotation);
}