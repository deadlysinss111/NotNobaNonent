// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/NNHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"

/*
* Mettre en place un composant de santé pour les acteurs
*   UHealthComponent* HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
*
*   Aplliquer des dégâts
*   TargetActor->TakeDamage(25.0f, FDamageEvent(), nullptr, nullptr);
*
*   Soigner l'entité
*   HealthComponent->Heal(25.0f);
*
*   Ecouter les événements(dans le BeginPlay() de l'acteur)
*   HealthComponent->OnHealthChanged.AddDynamic(this, &AMyCharacter::UpdateUI);
*   HealthComponent->OnDeath.AddDynamic(this, &AMyCharacter::HandleDeath);
*/


// Sets default values for this component's properties
UNNHealthComponent::UNNHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UNNHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* Owner = GetOwner();
    if (Owner)
    {
        // Enregistre la fonction HandleDamage sur l'événement OnTakeAnyDamage
        Owner->OnTakeAnyDamage.AddDynamic(this, &UNNHealthComponent::HandleDamage);
    }
}

void UNNHealthComponent::ApplyDamage(float Amount)
{
    if (Amount <= 0.0f || IsDead()) return;

    CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

void UNNHealthComponent::Heal(float Amount)
{
    if (Amount <= 0.0f || IsDead()) return; // Éviter de soigner un acteur mort

    CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);
}

// Gère les dégâts infligé
void UNNHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    ApplyDamage(Damage);
}
