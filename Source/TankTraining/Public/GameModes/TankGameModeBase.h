// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APlayerControllerBase;
/**
 *
 */
UCLASS()
class TANKTRAINING_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	APawnTank* PlayerTank;
	int32 NumOfEnermy = 0;
	APlayerControllerBase* PlayerControllerRef;
	void HandleGameOver(bool IsPlayerWon);
	int32 GetTargetTurretCount();
public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool IsPlayerWon);
};
