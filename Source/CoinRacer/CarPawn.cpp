#include "CarPawn.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "CoinRacer.h"
#include "WheeledVehicleMovementComponent4W.h"

static const FName SpeedInput("Speed");
static const FName TurnInput("Turn");

ACarPawn::ACarPawn()
{
	UWheeledVehicleMovementComponent4W* Car4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	//Adjust Tire Loading
	Car4W->MinNormalizedTireLoad = 0.0f;
	Car4W->MinNormalizedTireLoadFiltered = 0.2f;
	Car4W->MaxNormalizedTireLoad = 2.0f;
	Car4W->MaxNormalizedTireLoadFiltered = 2.0f;

	//Torque Settings
	Car4W->MaxEngineRPM = 5700.0f;
	Car4W->EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	Car4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, 1600.0f);
	Car4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1890.0f, 1800.0f);
	Car4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(5730.0f, 1700.0f);

	//Steer Settings
	Car4W->SteeringCurve.GetRichCurve()->Reset();
	Car4W->SteeringCurve.GetRichCurve()->AddKey(0.0f, 1.0f);
	Car4W->SteeringCurve.GetRichCurve()->AddKey(40.0f, 0.7f);
	Car4W->SteeringCurve.GetRichCurve()->AddKey(120.0f, 0.6f);

	//Front Wheel Spin
	Car4W->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_4W;
	Car4W->DifferentialSetup.FrontRearSplit = 0.75;

	//Automatic Car Gearbox
	Car4W->TransmissionSetup.bUseGearAutoBox = true;
	Car4W->TransmissionSetup.GearSwitchTime = 0.15f;
	Car4W->TransmissionSetup.GearAutoBoxLatency = 1.0f;

	//Attach Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;

	//Attach Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView = 90.f;

	CarCollision = CreateDefaultSubobject<UBoxComponent>("CarCollision");
	CarCollision->SetBoxExtent(FVector(100, 100, 100));
	CarCollision->SetupAttachment(RootComponent);
	CarCollision->GetGenerateOverlapEvents();
	CarCollision->OnComponentBeginOverlap.AddDynamic(this, &ACarPawn::OnComponentBeginOverlap);

	CoinsLeft = 20;
}

void ACarPawn::BeginPlay()
{
	Super::BeginPlay();

	FVector origin;
	FVector BoxExtent;
	this->GetActorBounds(true, origin, BoxExtent);
	CarCollision->SetBoxExtent(BoxExtent);
}

void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateInAirControl(DeltaTime);
}

void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Controls
	PlayerInputComponent->BindAxis(SpeedInput, this, &ACarPawn::ApplySpeed);
	PlayerInputComponent->BindAxis(TurnInput, this, &ACarPawn::ApplyTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACarPawn::LookUp);
	PlayerInputComponent->BindAxis("LookRound", this, &ACarPawn::LookRound);

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &ACarPawn::HandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &ACarPawn::HandbrakeReleased);

}

void ACarPawn::ApplySpeed(float val)
{
	GetVehicleMovementComponent()->SetThrottleInput(val);
}

void ACarPawn::ApplyTurn(float val)
{
	GetVehicleMovementComponent()->SetSteeringInput(val);
}

void ACarPawn::LookUp(float val)
{
	if (val != 0.f)
	{
		AddControllerPitchInput(val);
	}
}

void ACarPawn::LookRound(float val)
{
	if (val != 0.f)
	{
		AddControllerYawInput(val);
	}
}

void ACarPawn::HandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void ACarPawn::HandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void ACarPawn::UpdateInAirControl(float DeltaTime)
{
	if (UWheeledVehicleMovementComponent4W* Car4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement()))
	{
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		const FVector TraceStart = GetActorLocation() + FVector(0.f, 0.f, 50.f);
		const FVector TraceEnd = GetActorLocation() - FVector(0.f, 0.f, 200.f);

		FHitResult Hit;

		//Check if the car is in the air or flipped on the ground
		const bool InAir = !GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
		const bool HasFlipped = FVector::DotProduct(GetActorUpVector(), FVector::UpVector) < 0.1f;

		//Allow these movements if above requirements are met
		if (InAir || HasFlipped)
		{
			const float ForwardInput = InputComponent->GetAxisValue(SpeedInput);
			const float RightInput = InputComponent->GetAxisValue(TurnInput);

			const float AirMovementForcePitch = 1.f;
			const float AirMovementForceRoll = !InAir && HasFlipped ? 10.f : 1.f;

			if (UPrimitiveComponent* CarMesh = Car4W->UpdatedPrimitive)
			{
				const FVector MovementVector = FVector(RightInput * -AirMovementForceRoll, ForwardInput * AirMovementForcePitch, 0.f) * DeltaTime * 200.f;
				const FVector NewAngularMovement = GetActorRotation().RotateVector(MovementVector);

				CarMesh->SetPhysicsAngularVelocity(NewAngularMovement, true);
			}
		}
	}
}

void ACarPawn::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACoin::StaticClass()))
	{
		//Cast Other Actor 
		ACoin* coin = Cast<ACoin>(OtherActor);
		AActor* instigator = coin->GetInstigator();

		//Collect Coin
		coin->Destroy();
		--CoinsLeft;
		CoinTally();
	}
	if (OtherActor->IsA(ATrophy::StaticClass()))
	{

	}
}

void ACarPawn::CoinTally()
{
	if (CoinsLeft == 0)
	{
		ACoinSpawner trophy;
		trophy.SpawnTrophy();
	}
}
