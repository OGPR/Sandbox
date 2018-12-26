// Free to use, re-use, modify and share. 

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

//Empty macro for labelling parameters that are changed
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

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"))

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );
    UE_LOG(LogTemp, Warning, TEXT(" ViewPoint position is %s    ViewPoint rotation is %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())
    // Ray-cast out to reach distance

    // See what we hit (with the ray cast)
}

