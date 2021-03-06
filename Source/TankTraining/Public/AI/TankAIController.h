// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKTRAINING_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	bool IsDead() const;
protected:
	virtual void BeginPlay() override;
private:
	/*UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 300;*/
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;
};
