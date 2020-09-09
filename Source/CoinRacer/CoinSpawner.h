#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.h"
#include "Trophy.h"
#include "CoinSpawner.generated.h"

UCLASS()
class COINRACER_API ACoinSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ACoin> BP_Coin;

	UPROPERTY(Category = "Trophy", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ATrophy> BP_Trophy;

	FTimerHandle SpawnTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite)
		int32 NumberOfCoins;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite)
		int32 MaxWidthFloor;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite)
		int32 MaxDepthFloor;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite)
		int32 Height;

	UPROPERTY(EditAnywhere)
		float SpawnTime;

	void StartSpawns();

	void StopSpawns();

	void SpawnTrophy();

	FVector GetRandomLocation();

	FRotator RotateCoin();

	FRotator NoRotation();
};
