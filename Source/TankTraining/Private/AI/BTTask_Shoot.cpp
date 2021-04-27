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
	FVector LookAtTargetClean = FVector(PlayerTank->GetActorLocation().X, PlayerTank->GetActorLocation().Y, Tank->GetActorLocation().Z);
	FVector StartLocation = Tank->GetActorLocation();
	FRotator TurretRotation = Tank->GetTurretRotation();
	FRotator TurretTargetRotation = FVector(LookAtTargetClean - StartLocation).Rotation();

	//TurretTargetRotation.Yaw = FMath::FInterpConstantTo(TurretRotation.Yaw, TurretTargetRotation.Yaw, GetWorld()->DeltaTimeSeconds, 10.0f);
	Tank->RotateTurret(TurretTargetRotation);

	UE_LOG(LogTemp, Warning, TEXT("RotateTurret %s"), *TurretTargetRotation.ToString());
	if (TurretRotation.Yaw == TurretTargetRotation.Yaw) // turret straight to target
	{
		Tank->Fire();
	}
	return EBTNodeResult::Succeeded;
}