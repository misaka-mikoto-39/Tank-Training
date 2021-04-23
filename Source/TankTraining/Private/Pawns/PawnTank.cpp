// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/PawnTank.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Actors/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnTank::APawnTank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretComp = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Comp"));
	TurretComp->SetupAttachment(BaseMesh);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(TurretComp);

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(TurretMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(BarrelMesh);

	WheelBLComp = CreateDefaultSubobject<USceneComponent>(TEXT("Wheel BL Comp"));
	WheelBLComp->SetupAttachment(BaseMesh);
	WheelBLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel BL Mesh"));
	WheelBLMesh->SetupAttachment(WheelBLComp);

	WheelBRComp = CreateDefaultSubobject<USceneComponent>(TEXT("Wheel BR Comp"));
	WheelBRComp->SetupAttachment(BaseMesh);
	WheelBRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel BR Mesh"));
	WheelBRMesh->SetupAttachment(WheelBRComp);

	WheelFLComp = CreateDefaultSubobject<USceneComponent>(TEXT("Wheel FL Comp"));
	WheelFLComp->SetupAttachment(BaseMesh);
	WheelFLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel FL Mesh"));
	WheelFLMesh->SetupAttachment(WheelFLComp);

	WheelFRComp = CreateDefaultSubobject<USceneComponent>(TEXT("Wheel FR Comp"));
	WheelFRComp->SetupAttachment(BaseMesh);
	WheelFRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel FR Mesh"));
	WheelFRMesh->SetupAttachment(WheelFRComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
	// Move forward
	if (Value == 1)
	{
		LeftWheels = FORWARD;
		RightWheels = FORWARD;
	}
	// Move backward
	else if (Value == -1)
	{
		LeftWheels = BACKWARD;
		RightWheels = BACKWARD;
	}
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
	// Turn right
	if (Value == 1)
	{
		LeftWheels = FORWARD;
		RightWheels = BACKWARD;
	}
	// Turn left
	else if (Value == -1)
	{
		LeftWheels = BACKWARD;
		RightWheels = FORWARD;
	}
	//(LogTemp, Warning, TEXT("RotSationDirection, %d"), *Rotation.ToString());
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::RotateWheels()
{
	float RotateAmount;
	FRotator Rotation;
	// Left Wheels
	if (LeftWheels == FORWARD)
	{
		RotateAmount = -1 * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	}
	else if (LeftWheels == BACKWARD)
	{
		RotateAmount = 1 * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	}
	Rotation = FRotator(RotateAmount, 0, 0);
	WheelFLComp->AddLocalRotation(FQuat(Rotation));
	WheelBLComp->AddLocalRotation(FQuat(Rotation));

	// Right Wheels
	if (RightWheels == FORWARD)
	{
		RotateAmount = -1 * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	}
	else if (RightWheels == BACKWARD)
	{
		RotateAmount = 1 * MoveSpeed * GetWorld()->DeltaTimeSeconds;
	}
	Rotation = FRotator(RotateAmount, 0, 0);
	WheelFRComp->AddLocalRotation(FQuat(Rotation));
	WheelBRComp->AddLocalRotation(FQuat(Rotation));

	// Reset Wheels Rotation
	LeftWheels = NONE;
	RightWheels = NONE;
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::RotateTurret(FVector LookAtTarget)
{
	//CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 45.f);
	//FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FRotator TurretRotation = TurretMesh->GetComponentRotation();
	//FRotator TurretRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	TurretRotation.Yaw = FMath::FInterpConstantTo(TurretRotation.Yaw, LookAtTarget.Rotation().Yaw, GetWorld()->DeltaTimeSeconds, TurretRotateSpeed);
	UE_LOG(LogTemp, Warning, TEXT("TurretRotation: %s"), *TurretRotation.ToString());
	TurretMesh->SetWorldRotation(TurretRotation);
	SpringArm->SetWorldRotation(FRotator(SpringArm->GetComponentRotation().Pitch, TurretRotation.Yaw, SpringArm->GetComponentRotation().Roll));
}

void APawnTank::Fire()
{
	if (ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire"));
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		//SpawnRotation.Yaw -= 90;
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();
	RotateWheels();
	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;
		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}