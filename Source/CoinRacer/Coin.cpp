#include "Coin.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init Static Mesh
	CoinBody = CreateDefaultSubobject<UStaticMeshComponent>("CoinBody");
	this->RootComponent = CoinBody;
	CoinBody->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	//Collision
	CoinCollision = CreateDefaultSubobject<USphereComponent>("Coin Collision");
	CoinCollision->SetSphereRadius(40);
	CoinCollision->SetupAttachment(CoinBody);
	CoinCollision->GetGenerateOverlapEvents();
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

