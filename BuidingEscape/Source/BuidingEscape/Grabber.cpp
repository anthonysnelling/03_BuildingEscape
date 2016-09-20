// Anthony Snelling Copyright 2016

#include "BuidingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting for duty"));
	
	///look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//Physics Handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
	
	///look for attached physics Input Component (only Appears at Run time)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}
void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
}
// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRoation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRoation
		);

		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRoation.Vector() * Reach; 

			/// Draw a red trace in the world to visualize 
			DrawDebugLine(
				GetWorld(),
				PlayerViewPointLocation,
				LineTraceEnd,
				FColor(255, 0, 0),
				false,
				0.f,
				0.f,
				10.f
			);

	/// Setup query parameters
			FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-Trace (AKA Ray-cast) out to reach distance
			
			FHitResult Hit;
			GetWorld()->LineTraceSingleByObjectType(
				OUT Hit,
				PlayerViewPointLocation,
				LineTraceEnd,
				FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
				TraceParameters
			);

	///see what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(ActorHit->GetName()))
	}
}

