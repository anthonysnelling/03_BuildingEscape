// Anthony Snelling Copyright 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUIDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// How far ahead of the player can we reach in centimeters
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	//Ray-Cast and grab whats in reach
	void Grab();

	// Called when Grab is Released
	void Release();

	// Find Attached physics Handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) Attacehd Input Component
	void SetupInputComponent();

	//Return hit for first physics body in reach

	const FHitResult GetFirstPhysicsBodyInReach();

	// Returns current Start of reach line
	FVector GetReachLineStart();

	// Returns current end of reach line
	FVector GetReachLineEnd();
};