// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/TankGameModeBase.h"
#include "Pawns/PawnTank.h"
#include "Controllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformProcess.h"

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);
	}
	else if (APawnTank* DestroyedTank = Cast<APawnTank>(DeadActor))
	{
		DestroyedTank->PawnDestroyed();
		if (--NumOfEnermy == 0)
		{
			HandleGameOver(true);
		}
	}
}


int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TankActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTank::StaticClass(), TankActors);
	return TankActors.Num() - 1;
}

void ATankGameModeBase::BeginPlay()
{
	NumOfEnermy = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(true);
	}
}

void ATankGameModeBase::HandleGameOver(bool IsPlayerWon)
{
	GameOver(IsPlayerWon);
}