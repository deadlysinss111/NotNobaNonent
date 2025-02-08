// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/NNTriggerComponent.h"
#include "Components/BoxComponent.h"
#include <Components/CapsuleComponent.h>
#include "GameFramework/Character.h"
#include <Components/SphereComponent.h>

// Sets default values for this component's properties
UNNTriggerComponent::UNNTriggerComponent()
{
    // Créer un composant de collision par défaut
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));

    // Configurer des valeurs par défaut pour les collisions
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // Attacher les événements de collision
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNTriggerComponent::HandleBeginOverlap);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UNNTriggerComponent::HandleEndOverlap);
}

void UNNTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Owner is null!"));
        return;
    }

    // Vérifie si le RootComponent est déjà un composant de collision
    if (UPrimitiveComponent* RootCollision = Cast<UPrimitiveComponent>(OwnerActor->GetRootComponent()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Using RootComponent as collision component: %s"), *RootCollision->GetName());
        setCollisionComponent(RootCollision);
        return;
    }

    // Cherche un autre composant de collision
    TArray<UPrimitiveComponent*> PossibleCollisions;
    PossibleCollisions.Add(OwnerActor->FindComponentByClass<UBoxComponent>());
    PossibleCollisions.Add(OwnerActor->FindComponentByClass<UCapsuleComponent>());
    PossibleCollisions.Add(OwnerActor->FindComponentByClass<USphereComponent>());

    for (UPrimitiveComponent* Comp : PossibleCollisions)
    {
        if (Comp && Comp != OwnerActor->GetRootComponent())
        {
            UE_LOG(LogTemp, Warning, TEXT("Found a suitable collision component: %s"), *Comp->GetName());
            setCollisionComponent(Comp);
            return;
        }
    }
}


void UNNTriggerComponent::setCollisionComponent(UPrimitiveComponent* NewCollisionComponent)
{
    if (!NewCollisionComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("NewCollisionComponent is null! Cannot set collision component."));
        return;
    }

    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Owner is null!"));
        return;
    }

    if (CollisionComponent == NewCollisionComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("NewCollisionComponent is the same as the current one. Skipping."));
        return;
    }

    if (CollisionComponent)
    {
        CollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
        CollisionComponent->OnComponentEndOverlap.RemoveAll(this);
        CollisionComponent->DestroyComponent();
    }

    CollisionComponent = NewCollisionComponent;

    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNTriggerComponent::HandleBeginOverlap);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UNNTriggerComponent::HandleEndOverlap);
}


void UNNTriggerComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Vérifie si l'autre acteur n'est pas nul et n'est pas le propriétaire de ce composant
    if (OtherActor && OtherActor != GetOwner())
    {
        // Diffuse l'événement d'entrée d'acteur
        OnActorEnter.Broadcast(OtherActor);
    }
}

void UNNTriggerComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        OnActorExit.Broadcast(OtherActor);
    }
}
