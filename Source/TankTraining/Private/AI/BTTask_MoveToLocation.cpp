// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_MoveToLocation.h"
#include "Pawns/PawnTank.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	/*
	FVector LookAtTargetClean = FVector(PlayerTank->GetActorLocation().X, PlayerTank->GetActorLocation().Y, Tank->GetActorLocation().Z);
	FVector StartLocation = Tank->GetActorLocation();
	FRotator CameraRotation = Tank->GetCameraRotation();
	FRotator TurretTargetRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	if (FMath::FloorToInt(TurretTargetRotation.Yaw) != FMath::FloorToInt(CameraRotation.Yaw))
	{
		if (TurretTargetRotation.Yaw > CameraRotation.Yaw)
		{
			Tank->RotateCamera(1);
		}
		else
		{
			Tank->RotateCamera(-1);
		}
	}
	else
	{
		//Tank->Fire();
	}
*/
	UE_LOG(LogTemp, Warning, TEXT("Move to location"));
	return EBTNodeResult::Succeeded;
}