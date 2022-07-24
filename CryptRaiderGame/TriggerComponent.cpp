// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("Trigger Area Activated!!!"));
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Actor = GetAcceptableActor();
    //interaction function when it is a interactable object.
    if(Actor != nullptr)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if(Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
    }
  
}

// get the objects interacting in trigger area and check it has grabbable./interactable object and return that actor
AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for(AActor* OverlappedActor : Actors)
    {
        bool HasAcceptableTag = OverlappedActor->ActorHasTag(TagName);
        bool IsGrabbed = OverlappedActor->ActorHasTag("Grabbed");
        if(HasAcceptableTag && !IsGrabbed)
        {
          return OverlappedActor;
        }
    }

    return nullptr;

}

void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

