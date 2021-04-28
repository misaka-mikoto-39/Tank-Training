// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_MoveToLocation.h"
#include "AI/TankAIController.h"
#include "Pawns/PawnTank.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_MoveToLocation::UBTTask_MoveToLocation()
{
	NodeName = "Move To Location";
}
EBTNodeResult::Type UBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawnTank* Tank = Cast<APawnTank>(OwnerComp.GetAIOwner()->GetPawn());
	if (Tank == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	FVector LookAtTargetClean = FVector(TargetLocation.X, TargetLocation.Y, Tank->GetActorLocation().Z);
	FVector StartLocation = Tank->GetActorLocation();
	FRotator TankRotation = Tank->GetActorRotation();
	FRotator TankTargetRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	if (FMath::FloorToInt(TankTargetRotation.Yaw) != FMath::FloorToInt(TankRotation.Yaw))
	{
		if (TankTargetRotation.Yaw > TankRotation.Yaw)
		{
			Tank->CalculateRotateInput(1);
		}
		else
		{
			Tank->CalculateRotateInput(-1);
		}
	}
	else
	{
		Tank->CalculateMoveInput(1);
	}
	return EBTNodeResult::Succeeded;
}