// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/PawnTank.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::RotateTurret(FVector LookAtTarget)
{
	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Tick(DeltaTime);
	Rotate();
	Move();
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
	PlayerInputComponent->BindAxis("MoveLeft", this, &APawnTank::CalculateRotateInput);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}