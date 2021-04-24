// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/TankGameModeBase.h"
#include "Pawns/PawnTank.h"
#include "Controllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->PawnDestroyed();
		//HandleGameOver(false);
		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTank* DestroyedTank = Cast<APawnTank>(DeadActor))
	{
		DestroyedTank->PawnDestroyed();
		/*if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}*/
	}
}

void ATankGameModeBase::BeginPlay()
{
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(true);
	}
}