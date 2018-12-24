// Free to use, re-use, modify and share. 

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

    Owner = GetOwner();
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
	
}
void UOpenDoor::OpenDoor()
{
    auto Pitch = 0.f;
    auto Yaw = OpenAngle;
    auto Roll = 0.f;
    Owner->SetActorRotation(FRotator(Pitch, -Yaw, Roll));
}

void UOpenDoor::CloseDoor()
{
    auto Pitch = 0.f;
    auto Yaw = 0.f;
    auto Roll = 0.f;
    Owner->SetActorRotation(FRotator(Pitch, Yaw, Roll));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    //Poll the Trigger Volume
    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
        TimeLastDoorOpen = GetWorld()->GetTimeSeconds();
    }
    CloseDoor();

}


