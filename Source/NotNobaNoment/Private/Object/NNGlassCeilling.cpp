// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/NNGlassCeilling.h"

ANNGlassCeilling::ANNGlassCeilling()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UNNHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	HealthComponent->OnDeath.AddDynamic(this, &ThisClass::OnDeath);
}

void ANNGlassCeilling::BeginPlay()
{
	Super::BeginPlay();
	
	UPrimitiveComponent* ssx = Cast<UPrimitiveComponent>(GetRootComponent());

	if (UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("deactivated"));
		PhysComp->SetSimulatePhysics(false);
		PhysComp->SetEnableGravity(false);
	}
}

void ANNGlassCeilling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANNGlassCeilling::OnDeath() {
	if (UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("reactivated"));
		PhysComp->SetSimulatePhysics(true);
		PhysComp->SetEnableGravity(true);
	}
}