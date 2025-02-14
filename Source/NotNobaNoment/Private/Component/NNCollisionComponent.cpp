#include "Component/NNCollisionComponent.h"
#include "Components/BoxComponent.h"
#include <Components/CapsuleComponent.h>
#include <Components/SphereComponent.h>

UNNCollisionComponent::UNNCollisionComponent()
{
   // UE_LOG(LogTemp, Warning, TEXT("UNNCollisionComponent - Début du constructeur"));
    // Création d'un composant de collision par défaut
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));

    if (!CollisionComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("CollisionComponent est NULL au moment de la création !"));
        return;
    }


    //UE_LOG(LogTemp, Warning, TEXT("UNNCollisionComponent - CollisionComponent créé : %s"), *CollisionComponent->GetName());

    // Configuration des collisions
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Par défaut en mode Overlap
    CollisionComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap); // Par défaut en mode Overlap
    CollisionComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block); // Permet les hits

    // Attacher les événements de collision
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNCollisionComponent::HandleBeginOverlap);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UNNCollisionComponent::HandleEndOverlap);
    CollisionComponent->OnComponentHit.AddDynamic(this, &UNNCollisionComponent::HandleHit);

    //UE_LOG(LogTemp, Warning, TEXT("UNNCollisionComponent - Fin du constructeur"));

}

void UNNCollisionComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Owner is null!"));
        return;
    }

   // UE_LOG(LogTemp, Warning, TEXT("BeginPlay called for UNNCollisionComponent"));

    if (UPrimitiveComponent* RootCollision = Cast<UPrimitiveComponent>(OwnerActor->GetRootComponent()))
    {
       // UE_LOG(LogTemp, Warning, TEXT("Using RootComponent as collision component: %s"), *RootCollision->GetName());
        SetCollisionComponent(RootCollision);
        return;
    }

    TArray<UPrimitiveComponent*> PossibleCollisions;
    PossibleCollisions.Add(OwnerActor->FindComponentByClass<UBoxComponent>());
    PossibleCollisions.Add(OwnerActor->FindComponentByClass<UCapsuleComponent>());
    PossibleCollisions.Add(OwnerActor->FindComponentByClass<USphereComponent>());

    for (UPrimitiveComponent* Comp : PossibleCollisions)
    {
        if (Comp && Comp != OwnerActor->GetRootComponent())
        {
           // UE_LOG(LogTemp, Warning, TEXT("Found a suitable collision component: %s"), *Comp->GetName());
            SetCollisionComponent(Comp);
            return;
        }
    }

    //UE_LOG(LogTemp, Error, TEXT("The owner does not have a valid collision component"));
}

void UNNCollisionComponent::SetCollisionComponent(UPrimitiveComponent* NewCollisionComponent)
{
    if (!NewCollisionComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("NewCollisionComponent is null! Cannot set collision component."));
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
        CollisionComponent->OnComponentHit.RemoveAll(this);
    }

    CollisionComponent = NewCollisionComponent;

    //UE_LOG(LogTemp, Warning, TEXT("Setting up collision events for: %s"), *CollisionComponent->GetName());


    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UNNCollisionComponent::HandleBeginOverlap);
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UNNCollisionComponent::HandleEndOverlap);
    CollisionComponent->OnComponentHit.AddDynamic(this, &UNNCollisionComponent::HandleHit);

   // UE_LOG(LogTemp, Warning, TEXT("CollisionComponent successfully set to: %s"), *CollisionComponent->GetName());
}

void UNNCollisionComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        OnActorEnter.Broadcast(OtherActor);
    }
}

void UNNCollisionComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        OnActorExit.Broadcast(OtherActor);
    }
}

void UNNCollisionComponent::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != GetOwner())
    {
        OnActorHit.Broadcast(OtherActor, Hit);
    }
}
