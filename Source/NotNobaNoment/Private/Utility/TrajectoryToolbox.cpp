// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/TrajectoryToolbox.h"

TrajectoryToolbox::TrajectoryToolbox()
{
}

TrajectoryToolbox::~TrajectoryToolbox()
{
}


FVector TrajectoryToolbox::BellCurveInitialVelocity(FVector startPoint, FVector endPoint, float apex, float gravity)
{
    // Calculate distance and direction
    FVector direction = endPoint - startPoint;
    float horizontalDistance = FVector(direction.X, direction.Y, 0).Size();

    // Calculate the initial vertical velocity to reach the desired max height
    float vz0 = FMath::Sqrt(2 * gravity * apex);

    // Calculate the total time of flight (up and down)
    float timeToApex = vz0 / gravity;
    float totalTime = 2 * timeToApex;

    // Calculate the required horizontal velocity
    float vx0 = horizontalDistance / totalTime;

    // Combine horizontal and vertical velocities
    direction.Normalize();
    FVector initialVelocity = FVector(vx0 * direction.X, vx0 * direction.Y, vz0);

    return initialVelocity;
}


TArray<FVector> TrajectoryToolbox::LineRenderWithDirection(FVector origin, FVector direction, AActor* actorToIgnore, int splineSize, float step)
{
    TArray<FVector> pathPoints;

    // We initialize base values
    FVector virtualPos = origin;
    FVector nextPos;
    float overlap;
    FHitResult hit;

    // This loop will calculate next position, check if we hit something and add point to draw in prediction each iteration 
    for (int i = 1; i < splineSize; i++)
    {
        nextPos = virtualPos + direction * step;
        direction += FVector(0, 0, step * -1);
        pathPoints.Add(virtualPos);
        // Overlap our rays by small margin to ensure we never miss a surface
        overlap = FVector::Dist(virtualPos, nextPos) * 1.1f;

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(actorToIgnore); // Ignore self

        //When hitting a surface we want to show the surface marker and stop updating our line
        FVector normalizedDir = direction;
        normalizedDir.Normalize();
        if (GEngine->GetWorld()->LineTraceSingleByChannel(hit, virtualPos, normalizedDir * overlap, ECC_Visibility, QueryParams))
        {
            break;
        }

        virtualPos = nextPos;
    }

    return pathPoints;
}