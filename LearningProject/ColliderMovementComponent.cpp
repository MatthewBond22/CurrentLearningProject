	// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Accessing the Parent Function so that anything that happens in that will be accessable
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Check to see if things are valid
	//If everything is Null, it will just return nothing
	//Means everything is valid
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) 
	{
		return;
	}

	//Takes the Input Vector and Resets it to 0
	//Returns the Current Input then does as stated above
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//If we bump into something
		//Slide along the side
		if (Hit.IsValidBlockingHit()) {
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
			UE_LOG(LogTemp, Warning, TEXT("Hitting the Wall"));
		}
	}
}