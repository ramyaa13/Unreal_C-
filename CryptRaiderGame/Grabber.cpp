// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //Getting Physics Handle 
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	    PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

//Grab Object
void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	//Check whether it is a grabbable object
	bool HasHit = GetGrabbableInReach(HitResult);
	//if it is a grabbable object, grab the object.
	if(HasHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		UPrimitiveComponent* HitComponenet = HitResult.GetComponent();
		HitComponenet->SetSimulatePhysics(true);
		HitComponenet->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponenet,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

	}
}

//Check Whether it is a Grabbable Object and setting grab distance
bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		OutHitResult, 
		Start, End, 
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

	
	return HasHit;

}


// Release Object
void UGrabber::Release()
{
	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
	UE_LOG(LogTemp, Display, TEXT("Releaseddd"));
}

//Getting Physics Handle Component from the First Person Character
UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber needs Physics Handle Component"));
	}
	return Result;
}


