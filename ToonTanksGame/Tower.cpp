// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(InFireRange())
    {
       RotateTurret(Tank->GetActorLocation());
    }
    
}
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
void ATower::CheckFireCondition()
{

  if(InFireRange())
  {
     Fire();
  }

}

bool ATower::InFireRange()
{
    if(Tank)
    {
        //Find the distance to the Tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        
        // Check to see, if the Tank is in Range
        if(Distance <= FireRange)
        {
            // If in range, return true
            return true;
        }
    }

    return false;
}
