#include "TrophySpawner.h"
#include "CoinRacer.h"

// Sets default values
ATrophySpawner::ATrophySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TrophyCount = 14;
	MaxWidthFloor = 5500;
	MaxDepthFloor = 5500;
	Height = 30;
	SpawnTime = 0.1f;
}

// Called when the game starts or when spawned
void ATrophySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ATrophySpawner::StartSpawns, SpawnTime, true);
}

// Called every frame
void ATrophySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATrophySpawner::GetRandomLocation()
{
	return FVector(FMath::RandRange(-MaxWidthFloor, MaxWidthFloor), FMath::RandRange(-MaxDepthFloor, MaxDepthFloor), Height);
}

FRotator ATrophySpawner::RotateCoin()
{
	return FRotator(0, 0, 90.f);
}

void ATrophySpawner::StartSpawns()
{
	if (BP_Coin != NULL)
	{
		if (GetWorld() != NULL)
		{
			if (TrophyCount < 4)
			{
				StopSpawns();
			}
			else
			{
				FActorSpawnParameters sparams;
				sparams.Owner = this;
				--TrophyCount;
				FVector Location = GetRandomLocation();
				FRotator Rotator = RotateCoin();
				ACoin* trophy = GetWorld()->SpawnActor<ACoin>(BP_Coin, Location, Rotator, sparams);
			}
		}
	}
}

void ATrophySpawner::StopSpawns()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

