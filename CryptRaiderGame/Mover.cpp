// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = OriginalLocation;

    //if Object is places on the trigger, it moves to Moveoffset Location
	if(ShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
	}

	//if object is not on the trigger, it stays in Original Location.
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	//float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;
	float Speed = MoveOffset.Length() / MoveTime;
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);

}

//Set Should move Boolen from Trigger Component
void UMover::SetShouldMove(bool UpdatedShouldMove)
{
	ShouldMove = UpdatedShouldMove;
}

