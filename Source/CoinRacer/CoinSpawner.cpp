#include "CoinSpawner.h"
#include "CoinRacer.h"

// Sets default values
ACoinSpawner::ACoinSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NumberOfCoins = 14;
	MaxWidthFloor = 1000;
	MaxDepthFloor = 1000;
	Height = 30;
	SpawnTime = 0.3f;
}

// Called when the game starts or when spawned
void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ACoinSpawner::StartSpawns, SpawnTime, true);
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ACoinSpawner::StartSpawns, SpawnTime, true);
}

// Called every frame
void ACoinSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ACoinSpawner::GetRandomLocation()
{
	return FVector(FMath::RandRange(-MaxWidthFloor, MaxWidthFloor), FMath::RandRange(-MaxDepthFloor, MaxDepthFloor), Height);
}

FRotator ACoinSpawner::RotateCoin()
{
	return FRotator(0, 0, 90.f);
}

FRotator ACoinSpawner::NoRotation()
{
	return FRotator(0, 0, 0);
}

void ACoinSpawner::StartSpawns()
{
	if (BP_Coin != NULL)
	{
		if (GetWorld() != NULL)
		{
			if (NumberOfCoins < 4)
			{
				StopSpawns();
			}
			else
			{
				FActorSpawnParameters sparams;
				sparams.Owner = this;
				--NumberOfCoins;
				FVector Location = GetRandomLocation();
				FRotator Rotator = RotateCoin();
				ATrophy* trophy = GetWorld()->SpawnActor<ATrophy>(BP_Trophy, Location, Rotator, sparams);

				ACoin* Coin = GetWorld()->SpawnActor<ACoin>(BP_Coin, Location, Rotator, sparams);

			}
		}
	}
}

void ACoinSpawner::StopSpawns()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	//GetWorldTimerManager().ClearTimer(SpawnTrophyHandle);
}

void ACoinSpawner::SpawnTrophy()
{
	if (BP_Trophy != NULL)
	{
		if (GetWorld() != NULL)
		{
			FActorSpawnParameters sparams;
			sparams.Owner = this;

			FVector Location = GetRandomLocation();
			FRotator Rotator = NoRotation();

			ATrophy* Trophy = GetWorld()->SpawnActor<ATrophy>(BP_Trophy, Location, Rotator, sparams);

		}
	}
}