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

    if (!IsInFireRange()) return;
    RotateTurret(Tank->GetActorLocation());
}

void ATower::CheckFireCondition()
{
    if (!IsInFireRange()) return;
    Fire();
}

bool ATower::IsInFireRange() {
    if (!Tank) return false;
    // Get distance to tank, check if in range then rotate towards tank
    float dist = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    if (dist > FireRange) return false;
    return true;
}