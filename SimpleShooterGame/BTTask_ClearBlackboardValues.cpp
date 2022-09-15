// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValues.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardValues::UBTTask_ClearBlackboardValues()
{
    NodeName = TEXT("Clear Blackboard Values");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValues::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    return EBTNodeResult::Succeeded;
}


