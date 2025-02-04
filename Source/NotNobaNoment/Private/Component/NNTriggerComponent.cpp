// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/NNTriggerComponent.h"
#include "Components/BoxComponent.h"
#include <Components/CapsuleComponent.h>

// Sets default values for this component's properties
UNNTriggerComponent::UNNTriggerComponent()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));

	// Configurer des valeurs par défaut pour les collisions
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Attacher les événements de collision
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNTriggerComponent::HandleBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UNNTriggerComponent::HandleEndOverlap);
}

// Called when the game starts
void UNNTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->AttachToComponent(
		GetOwner()->GetRootComponent(),
		FAttachmentTransformRules::KeepRelativeTransform
	);
}

void UNNTriggerComponent::setCollisionComponent(UPrimitiveComponent* NewCollisionComponent)
{
    if (USceneComponent* SceneComp = Cast<USceneComponent>(NewCollisionComponent))
    {
        if (GetOwner() && GetOwner()->GetRootComponent())
        {
            SceneComp->AttachToComponent(
                GetOwner()->GetRootComponent(),
                FAttachmentTransformRules::KeepRelativeTransform
            );
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Owner or RootComponent is null!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NewCollisionComponent is not a USceneComponent and cannot be attached!"));
        return;
    }

    // Détacher les anciens événements
    if (CollisionComponent)
    {
        CollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
        CollisionComponent->OnComponentEndOverlap.RemoveAll(this);
    }

    // Mettre à jour la référence du composant
    CollisionComponent = NewCollisionComponent;

    // Réattacher les événements de collision
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
