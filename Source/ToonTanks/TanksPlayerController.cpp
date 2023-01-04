#include "TanksPlayerController.h"
#include "GameFramework/Pawn.h"

void ATanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = bPlayerEnabled;
}