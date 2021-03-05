#include "Collider_Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ColliderMovementComponent.h"

// Sets default values
ACollider_Pawn::ACollider_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Unneeded if you make the SphereComponent
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	//SphereComponent->SetupAttachment(GetRootComponent());
	SetRootComponent(SphereComponent);

	SphereComponent->InitSphereRadius(40.f);
	//Sets the Sphere's collion profile name
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(GetRootComponent());

	//Finds a Static Mesh, This is used for HARDCODING a Mesh to an object
	//Typically it is easier to do it inengine, but this can be done for time sake
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	//Initilization of the Mesh Component Asset
	//Checks to see if there is a Mesh in the location Specified in the MeshComponentAsset area
	//If it has Succeeded it will replace the mesh Component with the Asset that it has found
	if (MeshComponentAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		MeshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	}

	//Spring Arm allows for a slight delay to the camera behind the player
	//Spring Arm component and parent a Camera component to it so that our camera can expand/retract based on gameplay situations (Taken From UE4 Page)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MyMovementComponent = CreateDefaultSubobject<UColliderMovementComponent>(TEXT("MyMovementComponent"));
	MyMovementComponent->UpdatedComponent = RootComponent;

	CameraInput = FVector2D(0.f, 0.f);

	//Allows us to Possess the Pawn on Launch
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void ACollider_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollider_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Creating the Ability to rotate the Camera
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	FRotator NewSpringArmRotator = SpringArm->GetComponentRotation();
	//Locks the Up and down motion to a certain set of values
	//Allows us to make sure the player cannot ruin the camera for consistant play
	NewSpringArmRotator.Pitch = FMath::Clamp(NewSpringArmRotator.Pitch += CameraInput.Y, -80.f, -15.f);
	
	SpringArm->SetWorldRotation(NewSpringArmRotator);
}

// Called to bind functionality to input
void ACollider_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Setting up the players input to the game

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBack"), this, &ACollider_Pawn::MoveForwardBack);

	PlayerInputComponent->BindAxis(TEXT("MoveRightLeft"), this, &ACollider_Pawn::MoveRightLeft);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider_Pawn::PitchCamera);

	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider_Pawn::YawCamera);
}


//Provides the Pawn with Movement controls
void ACollider_Pawn::MoveForwardBack(float input)
{
	FVector Forward = GetActorForwardVector();

	if (MyMovementComponent)
	{
		MyMovementComponent->AddInputVector(Forward * input);
	}

}
void ACollider_Pawn::MoveRightLeft(float input)
{
	FVector Right = GetActorRightVector();
	if (MyMovementComponent)
	{
		MyMovementComponent->AddInputVector(Right * input);
	}
}

//Sets the Input for the camera controls
void ACollider_Pawn::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ACollider_Pawn::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}


//Overrides the base movement Component with our own one
//This is done to allow full control of the movement component
UPawnMovementComponent* ACollider_Pawn::GetMovementComponent() const
{
	return MyMovementComponent;
}
