#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Trophy.generated.h"

UCLASS()
class COINRACER_API ATrophy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrophy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* TrophyBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* TrophyCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
