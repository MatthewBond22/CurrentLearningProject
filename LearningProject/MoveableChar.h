// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MoveableChar.generated.h"

UCLASS()
class LEARNINGPROJECT_API AMoveableChar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMoveableChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Allows for the Mesh Component to be created
	//Makes it Editable anywhere in the main editor and puts the Mesh Component
	//under the category of Model Mesh for easy lookup
	UPROPERTY(EditAnywhere, Category = "Model Properties")
	class USkeletalMeshComponent* MeshComponent;

	//Creates a Camera that is attached to the Player
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	//Creates the player speed and allows it to be set anywhere in the editor
	UPROPERTY(EditAnywhere, Category = "Movement Speed")
	float MaxSpeed;

private:

	//A Void that allows for the Movement of Backwards and Forwards
	//Is set to a float value that allows for it to be Dynamic
	void MoveForwardBack(float Value);
	void MoveRightLeft(float Value);

	//Creates the Current Velocity float which is used for movement
	FVector CurrentVelocity;
};
