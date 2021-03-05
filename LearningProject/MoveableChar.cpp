// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableChar.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"


//Check UE4 Documentiaton if needing to include anything
//Don't be afraid to search it up online if needing to



// Sets default values
AMoveableChar::AMoveableChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Construction and Inilization of the Root Component of the Pawn Class
	//There is no need to make this in the .h file as it already inherits it from Actor.h
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Construction of the Mesh Component of the Pawn Class
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));

	//Attaching the Mesh Component to the Root Component
	//Good Knowledge to make sure these are attached and what is attached to what
	MeshComponent->SetupAttachment(GetRootComponent());

	//Constuction of the Camera Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Attaching the Camera to the Root Component
	Camera->SetupAttachment(GetRootComponent());
	//Sets the Location of the Camera Relative to Space
	Camera->SetRelativeLocation(FVector(-400.f, 0.f, 100.f));
	//Sets the Rotation of the Camera Relative to Space
	Camera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	//Allows us to take control of the player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Sets the base Velocity of the Player
	CurrentVelocity = FVector(0.f);

	//Sets the Max Speed of the player
	MaxSpeed = 0.f;
}

// Called when the game starts or when spawned
void AMoveableChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveableChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Gets the Actors Location and Adds the Velocity * The Tick of the Game
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);

	//Sets the Actors new location based off these Values
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void AMoveableChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Setting up the players input to the game
	PlayerInputComponent->BindAxis(TEXT("MoveForwardBack"), this, &AMoveableChar::MoveForwardBack);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"), this, &AMoveableChar::MoveRightLeft);

}
//Callable void for Moving Forward and Backwards
void AMoveableChar::MoveForwardBack(float Value)
{
	CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
}
//Callable void for Moving Right and Left
void AMoveableChar::MoveRightLeft(float Value) 
{
	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
}