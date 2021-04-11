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

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(TurretMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(BarrelMesh);

	WheelBLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel BL Mesh"));
	WheelBLMesh->SetupAttachment(BaseMesh);

	WheelBRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel BR Mesh"));
	WheelBRMesh->SetupAttachment(BaseMesh);

	WheelFLMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel FL Mesh"));
	WheelFLMesh->SetupAttachment(BaseMesh);

	WheelFRMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel FR Mesh"));
	WheelFRMesh->SetupAttachment(BaseMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}