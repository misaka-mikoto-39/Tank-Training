// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_MoveToLocation.h"



UBTTask_MoveToLocation::UBTTask_MoveToLocation()
{
	NodeName = "Move To Location";
}
EBTNodeResult::Type UBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UE_LOG(LogTemp, Warning, TEXT("Move to location"));
	return EBTNodeResult::Succeeded;
}
