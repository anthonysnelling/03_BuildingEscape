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
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRoation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRoation
		);
	// TODO log out to test
		UE_LOG(LogTemp, Warning, TEXT("Location: %s, Roatation: %s"), 
			*PlayerViewPointLocation.ToString(),
			*PlayerViewPointRoation.ToString()
			);

	// Ray-cast out to reach distance

	//see what we hit
}

