// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTask_Shoot.h"
#include "AI/TankAIController.h"
#include "Pawns/PawnTank.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	APawn* PlayerTank = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerTank == nullptr)
	{
		return EBTNodeResult::Failed;
	}
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
	return EBTNodeResult::Succeeded;
}