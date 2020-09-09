#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Coin.generated.h"

UCLASS()
class COINRACER_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* CoinBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* CoinCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
