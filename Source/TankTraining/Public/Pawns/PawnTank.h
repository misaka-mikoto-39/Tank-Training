// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnTank.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class AProjectileBase;
class UHealthComponent;

UENUM()
enum WheelRotation
{
	FORWARD,
	BACKWARD,
	NONE
};

UCLASS()
class TANKTRAINING_API APawnTank : public APawn
{
	GENERATED_BODY()

private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* TurretComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BarrelMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* WheelBLComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelBLMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* WheelBRComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelBRMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* WheelFLComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelFLMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* WheelFRComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelFRMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

	//VARIALES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* ShootParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* DeathSound;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotateSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float FireRate = 1.0f; // 1 per 1 second

	FVector MoveDirection;
	WheelRotation LeftWheels = NONE;
	WheelRotation RightWheels = NONE;
	FQuat RotationDirection;
	bool IsAmmoLoaded = true;
	FTimerHandle FireRateTimerHandle;

	void Move();
	void Rotate();
	void RotateWheels();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HandleDestruction();
public:
	// Sets default values for this pawn's properties
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FRotator GetCameraRotation() const;
	void SetCameraRotation(FRotator NewRotation);
	void PawnDestroyed();
	void RotateCamera(float Value);
	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);
	void RotateTurret(FRotator NewRotation);
	virtual void Fire();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
		bool IsDead() const;
	void ReloadAmmo();
	UFUNCTION(BlueprintPure)
		float GetReloadPercent() const;
	UFUNCTION(BlueprintPure)
		bool GetIsAmmoLoaded() const;
};
