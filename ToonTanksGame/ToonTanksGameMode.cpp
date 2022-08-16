// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"

// Called when the game starts or when spawned
void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

     if(ToonTanksPlayerController)
     {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &ToonTanksPlayerController::SetPlayerEnabledState(true),
            true
        );
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay;
            false
        );
     }

}
void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{

    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        //Game Lose
        GameOver(false);
    }
    else if(AActor* DestroyedTower = cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;

        if(TargetTowers == 0)
        {
            //Game Win
            GameOver(true);
        }
    }

}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();

}