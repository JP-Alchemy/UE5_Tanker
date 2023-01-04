#include "TanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "TanksPlayerController.h"

void ATanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (TanksPlayerController)
        {
            TanksPlayerController->SetPlayerEnabledState(false);
        }
    }
    else if (ATower *deadTower = Cast<ATower>(DeadActor))
    {
        deadTower->HandleDestruction();
    }
}

void ATanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TanksPlayerController = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (!TanksPlayerController) return;
    TanksPlayerController->SetPlayerEnabledState(false);
    FTimerHandle playerEnableTimerHandle;
    FTimerDelegate enabledDelegate = FTimerDelegate::CreateUObject(TanksPlayerController, &ATanksPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(playerEnableTimerHandle, enabledDelegate, StartDelay, false);
}