// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BounceProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TANKTRAINING_API ABounceProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
		float MovementSpeed = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float Damage = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bounce", meta = (AllowPrivateAccess = "true"))
		float TotalJump = 4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bounce", meta = (AllowPrivateAccess = "true"))
		float CurrentJump = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bounce", meta = (AllowPrivateAccess = "true"))
		float SearchingRadius = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bounce", meta = (AllowPrivateAccess = "true"))
		UClass* TargetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bounce", meta = (AllowPrivateAccess = "true"))
		UClass* BounceClass;
	AActor* CurrentActor;
	TArray<AActor*> ActorsToIgnoreList;
	TArray<AActor*> OutActorsList;
public:
	// Sets default values for this actor's properties
	ABounceProjectile();
	void SetData(AActor* InCurrentActor, const TArray<AActor*>& InActorsToIgnoreList, const float InCurrentJump);
	virtual void SetOwner(AActor* NewOwner) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
