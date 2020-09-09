#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trophy.h"
#include "Coin.h"
#include "TrophySpawner.generated.h"

UCLASS()
class COINRACER_API ATrophySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrophySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Trophy", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ATrophy> BP_Trophy;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ACoin> BP_Coin;

	FTimerHandle SpawnTimerHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite)
		int32 TrophyCount;

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

	FVector GetRandomLocation();

	FRotator RotateCoin();
};
