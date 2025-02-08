// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/NNTriggerComponent.h"
#include "Components/BoxComponent.h"
#include <Components/CapsuleComponent.h>
#include "GameFramework/Character.h"
#include <Components/SphereComponent.h>

// Sets default values for this component's properties
UNNTriggerComponent::UNNTriggerComponent()
{
	// Cr�er un composant de collision par d�faut
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));

	// Configurer des valeurs par d�faut pour les collisions
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Attacher les �v�nements de collision
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNTriggerComponent::HandleBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UNNTriggerComponent::HandleEndOverlap);
}


// Called when the game starts
void UNNTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	//// V�rifie si le owner poss�de dans �a hierarchie un box component ou un capsule component ou un sphere component
	//if (GetOwner()->FindComponentByClass<UBoxComponent>())
	//{
	//	setCollisionComponent(GetOwner()->FindComponentByClass<UBoxComponent>());
	//}
	//else if (GetOwner()->FindComponentByClass<UCapsuleComponent>())
	//{
	//	setCollisionComponent(GetOwner()->FindComponentByClass<UCapsuleComponent>());
	//}
	//else if (GetOwner()->FindComponentByClass<USphereComponent>())
	//{
	//	setCollisionComponent(GetOwner()->FindComponentByClass<USphereComponent>());
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("The owner does not have a valid collision component"));
	//}
}

void UNNTriggerComponent::setCollisionComponent(UPrimitiveComponent* NewCollisionComponent)
{
    if (USceneComponent* SceneComp = Cast<USceneComponent>(NewCollisionComponent))
    {
        if (GetOwner() && GetOwner()->GetRootComponent() && GetOwner()->GetRootComponent() != NewCollisionComponent)
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

    // D�tacher les anciens �v�nements
    if (CollisionComponent)
    {
        CollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
        CollisionComponent->OnComponentEndOverlap.RemoveAll(this);
    }

	//Supprimer l'ancien composant de collision
	CollisionComponent->DestroyComponent();

    // Mettre � jour la r�f�rence du composant
    CollisionComponent = NewCollisionComponent;

    // R�attacher les �v�nements de collision
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNTriggerComponent::HandleBeginOverlap);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UNNTriggerComponent::HandleEndOverlap);
}

void UNNTriggerComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// V�rifie si l'autre acteur n'est pas nul et n'est pas le propri�taire de ce composant
	if (OtherActor && OtherActor != GetOwner())
	{
		// Diffuse l'�v�nement d'entr�e d'acteur
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
