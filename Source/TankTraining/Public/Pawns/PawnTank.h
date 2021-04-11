// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnTank.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

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
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BarrelMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelBLMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelBRMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelFLMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WheelFRMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
