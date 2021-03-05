// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ColliderMovementComponent.h"
#include "Collider_Pawn.generated.h"

UCLASS()
class LEARNINGPROJECT_API ACollider_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Creates a class for the Static Mesh Component
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;
	
	//Creates a Camera Component
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;

	//Creates a Spring Arm component
	//
	//INSERT SPRING ARM USES HERE
	//
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* SpringArm;

	//Creating a class for the Custom MovementComponent
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UColliderMovementComponent* MyMovementComponent;

	//Creating the Override of the Movement Component
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	//Return Type for the MeshComponent
	//FORCEINLINE works as a macro, it will paste the { return MeshComponent;  }
	//anywhere that GetMeshComponent() is called
	//This is known as a "Getter"
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent;  }
	//This is known as a "Setter"
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Mesh) { MeshComponent = Mesh; }

	//The Getters and Setters for the Sphere component
	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent; }
	FORCEINLINE void SetSphereComponent(USphereComponent* Sphere) { SphereComponent = Sphere; }

	//Getters and Setters for the Camera Component and Spring Arm Component
	FORCEINLINE UCameraComponent* GetCameraComponent() { return Camera; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* InCamera) { Camera = InCamera; }
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* InSpringArm) { SpringArm = InSpringArm; }

private:

		void MoveForwardBack(float input);
		void MoveRightLeft(float input);

		void PitchCamera(float AxisValue);
		void YawCamera(float AxisValue);

		FVector2D CameraInput;
};
