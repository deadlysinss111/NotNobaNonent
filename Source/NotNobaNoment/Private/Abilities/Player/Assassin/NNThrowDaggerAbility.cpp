// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Player/Assassin/NNThrowDaggerAbility.h"
#include "Utility/TrajectoryToolbox.h"

void UNNThrowDaggerAbility::Init(APawn* owner) {
	Super::Init(owner);

	_currentAction.BindUFunction(this, FName("RenderCurve"));


	TArray<AActor*> AttachedActors;
	_owner->GetAttachedActors(AttachedActors);
	for (AActor* Child : AttachedActors)
	{
		ANNDagger* dagger = Cast<ANNDagger>(Child);
		if (dagger)
		{
			_dagger = dagger;
		}
	}

    FString AssetPath = FString::Printf(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    _mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), this, *AssetPath));

    AssetPath = FString::Printf(TEXT("Material'/Game/StarterContent/Materials/M_AssetPlatform.M_AssetPlatform'"));
    _material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), this, *AssetPath));


    _spline = NewObject<USplineComponent>(_owner);
    _spline->RegisterComponent();
    _spline->AttachToComponent(_owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

    _splineMeshes.Reserve(SPLINE_SIZE);
}

void UNNThrowDaggerAbility::Trigger(KeyState state) {
	_currentAction.Execute(state);
}

void UNNThrowDaggerAbility::Throw(KeyState state) {
	_dagger->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (UPrimitiveComponent* PhysComp = Cast<UPrimitiveComponent>(_dagger->GetRootComponent()))
	{
		PhysComp->SetSimulatePhysics(true);
		FVector ForwardDirection = _owner->FindComponentByClass<USkeletalMeshComponent>()->GetComponentRotation().Vector() * 1.0f;
        ForwardDirection = ForwardDirection.RotateAngleAxis(90.0f, FVector(0, 0, 1));
		FVector Force = ForwardDirection * 100000;
		PhysComp->AddImpulse(Force);
	}

	_dagger->ChangeState(ANNDagger::DaggerState::Flying);
	_currentAction.BindUFunction(this, FName("Jump"));
}

void UNNThrowDaggerAbility::Jump(KeyState state) {
    if (state != KeyState::End) return;

    _owner->SetActorLocation(_dagger->GetActorLocation());
	_currentAction.BindUFunction(this, FName("RenderCurve"));
	_currentAction.BindUFunction(this, FName("RenderCurve"));
}

void UNNThrowDaggerAbility::ResetCurve() {
    for(USplineMeshComponent* mesh : _splineMeshes) {
        mesh->ConditionalBeginDestroy();
    }
    _splineMeshes.Reset(SPLINE_SIZE);
    _spline->ClearSplinePoints();
}

void UNNThrowDaggerAbility::RenderCurve(KeyState state) {
    ResetCurve();

    if (state == KeyState::End) {
        _currentAction.BindUFunction(this, FName("Throw"));
        Trigger(state);
        return;
    }

    FVector direction;
    {
        FHitResult HitResult;
        FVector start = _owner->GetActorLocation();
        FVector end = (_owner->FindComponentByClass<USkeletalMeshComponent>()->GetComponentRotation().Vector() * 1.0f);
        end = end.RotateAngleAxis(90.0f, FVector(0, 0, 1));
        end += start;

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(_owner);

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, start, end, ECC_Visibility, QueryParams);

        direction = TrajectoryToolbox::BellCurveInitialVelocity(start, end, .05f, 1000);
    }

    TArray<FVector> points = TrajectoryToolbox::LineRenderWithDirection(_owner->GetNavAgentLocation(), direction, _owner, SPLINE_SIZE);

    for (const FVector& point : points) {
        _spline->AddSplinePoint(point, ESplineCoordinateSpace::World);
    }    

    int NumPoints = _spline->GetNumberOfSplinePoints();
    for (int i = 0; i < NumPoints - 1; i++) {
        USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(_owner);
        _splineMeshes.Add(SplineMesh);
        SplineMesh->RegisterComponent();
        //SplineMesh->AttachToComponent(_spline, FAttachmentTransformRules::KeepRelativeTransform);
        SplineMesh->SetMobility(EComponentMobility::Movable);
        SplineMesh->SetStaticMesh(_mesh);
        if (_material) {
            SplineMesh->SetMaterial(0, _material);
        }

        FVector StartPos = _spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector StartTangent = _spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
        FVector EndPos = _spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
        FVector EndTangent = _spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

        SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
    }
}