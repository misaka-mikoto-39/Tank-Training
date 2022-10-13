// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/BounceProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Pawns/PawnTank.h"
// Sets default values
ABounceProjectile::ABounceProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABounceProjectile::OnHit);
	RootComponent = ProjectileMesh;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->ProjectileGravityScale = 0;
	InitialLifeSpan = 5.0f;
}

void ABounceProjectile::SetData(AActor* InCurrentActor, const TArray<AActor*>& InActorsToIgnoreList, const float InCurrentJump)
{
	CurrentActor = InCurrentActor;
	ProjectileMesh->IgnoreActorWhenMoving(CurrentActor, true);
	ActorsToIgnoreList = InActorsToIgnoreList;
	CurrentJump = InCurrentJump;
}

void ABounceProjectile::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	if (CurrentJump == 0) // first shot
	{
		ActorsToIgnoreList.AddUnique(NewOwner);
		ProjectileMesh->IgnoreActorWhenMoving(NewOwner, true);
	}
}

// Called when the game starts or when spawned
void ABounceProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ABounceProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DrawDebugSphere(GetWorld(), OtherActor->GetActorLocation(), 10, 26, FColor::Green, false, 5.0f, 0, 1.0f);
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}
	if (OtherActor && OtherActor != this && OtherActor != MyOwner && OtherActor != CurrentActor)
	{
		CurrentActor = OtherActor;
		ActorsToIgnoreList.AddUnique(CurrentActor);
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		//UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		if (CurrentJump++ <= TotalJump)
		{
			DrawDebugSphere(GetWorld(), CurrentActor->GetActorLocation(), SearchingRadius, 26, FColor::Green, false, 5.0f, 0, 1.0f);
			if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), CurrentActor->GetActorLocation(), SearchingRadius, ObjectTypes, TargetClass, ActorsToIgnoreList, OutActorsList))
			{
				//add next actor to ignore list
				ActorsToIgnoreList.Append(OutActorsList);
				for (auto TargetActor : OutActorsList)
				{
					DrawDebugLine(GetWorld(), CurrentActor->GetActorLocation(), TargetActor->GetActorLocation(), FColor::Red, false, 5, 0, 1);
					FVector SpawnLocation = CurrentActor->GetActorLocation();
					//calculate bounce direction
					FRotator SpawnRotation = (TargetActor->GetActorLocation() - CurrentActor->GetActorLocation()).Rotation();
					DrawDebugSphere(GetWorld(), TargetActor->GetActorLocation(), 10, 26, FColor::Red, false, 5.0f, 0, 1.0f);
					//spawn projectile
					ABounceProjectile* TempProjectile = GetWorld()->SpawnActor<ABounceProjectile>(BounceClass, SpawnLocation, SpawnRotation);
					TempProjectile->SetData(CurrentActor, ActorsToIgnoreList, CurrentJump);
					TempProjectile->SetOwner(this->GetOwner());
				}
			}
		}
		Destroy();
	}
}