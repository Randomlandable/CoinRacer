#include "Trophy.h"

// Sets default values
ATrophy::ATrophy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Init Static Mesh
	TrophyBody = CreateDefaultSubobject<UStaticMeshComponent>("TrophyBody");
	this->RootComponent = TrophyBody;
	TrophyBody->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	//Collision
	TrophyCollision = CreateDefaultSubobject<USphereComponent>("Trophy Collision");
	TrophyCollision->SetSphereRadius(100);
	TrophyCollision->SetupAttachment(TrophyBody);
	TrophyCollision->GetGenerateOverlapEvents();
}

// Called when the game starts or when spawned
void ATrophy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrophy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

