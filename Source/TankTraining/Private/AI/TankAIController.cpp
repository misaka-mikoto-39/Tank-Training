// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TankAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Pawns/PawnTank.h"

bool ATankAIController::IsDead() const
{
	APawnTank* ControlledTank = Cast<APawnTank>(GetPawn());
	if (ControlledTank != nullptr)
	{
		return ControlledTank->IsDead();
	}
	return true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		//GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
