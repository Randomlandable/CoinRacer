#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "WheeledVehicle.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Coin.h"
#include "Trophy.h"
#include "CoinSpawner.h"
#include "CarPawn.generated.h"

/**
 * 
 */
UCLASS()
class COINRACER_API ACarPawn : public AWheeledVehicle
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ACarPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//Speed and steering
	void ApplySpeed(float val);
	void ApplyTurn(float val);

	//Mouse movement
	void LookUp(float val);
	void LookRound(float val);

	//Handbrake
	void HandbrakePressed();
	void HandbrakeReleased();

	//Car air physics
	void UpdateInAirControl(float DeltaTime);

	void CoinTally();
	
	UPROPERTY(Category = "Coin", EditAnywhere, BlueprintReadWrite)
		int32 CoinsLeft;

	void SpawnTrophy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* CarCollision;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
