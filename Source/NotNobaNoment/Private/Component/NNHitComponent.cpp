//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Component/NNHitComponent.h"
//
//// Sets default values for this component's properties
//UNNHitComponent::UNNHitComponent()
//{
//	// Créer un composant de collision par défaut
//	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
//
//	// Configurer des valeurs par défaut pour les collisions
//	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
//	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
//
//	// Attacher les événements de collision
//	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNTriggerComponent::HandleHit);
//}
//
//
//void UNNHitComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// Vérifie si le owner posséde dans ça hierarchie un box component ou un capsule component ou un sphere component
//	if (GetOwner()->FindComponentByClass<UBoxComponent>())
//	{
//		setCollisionComponent(GetOwner()->FindComponentByClass<UBoxComponent>());
//	}
//	else if (GetOwner()->FindComponentByClass<UCapsuleComponent>())
//	{
//		setCollisionComponent(GetOwner()->FindComponentByClass<UCapsuleComponent>());
//	}
//	else if (GetOwner()->FindComponentByClass<USphereComponent>())
//	{
//		setCollisionComponent(GetOwner()->FindComponentByClass<USphereComponent>());
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("The owner does not have a valid collision component"));
//	}
//}
//
//void UNNHitComponent::setCollisionComponent(UPrimitiveComponent* NewCollisionComponent)
//{
//	if (USceneComponent* SceneComp = Cast<USceneComponent>(NewCollisionComponent))
//	{
//		if (GetOwner() && GetOwner()->GetRootComponent())
//		{
//			SceneComp->AttachToComponent(
//				GetOwner()->GetRootComponent(),
//				FAttachmentTransformRules::KeepRelativeTransform
//			);
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Owner or RootComponent is null!"));
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("NewCollisionComponent is not a USceneComponent and cannot be attached!"));
//		return;
//	}
//
//	// Détacher les anciens événements
//	if (CollisionComponent)
//	{
//		CollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
//		CollisionComponent->OnComponentEndOverlap.RemoveAll(this);
//	}
//
//	// Mettre à jour la référence du composant
//	CollisionComponent = NewCollisionComponent;
//
//	// Réattacher les événements de collision
//	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNHitComponent::HandleHit);
//}
//
//void UNNHitComponent::HandleHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	// Vérifie si l'autre acteur n'est pas nul et n'est pas le propriétaire de ce composant
//	if (OtherActor && OtherActor != GetOwner())
//	{
//		// Diffuse l'événement d'entrée d'acteur
//		OnActorEnter.Broadcast(OtherActor);
//	}
//}