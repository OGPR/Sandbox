// Free to use, re-use, modify and share. 

#include "PositionReporterRock.h"
#include <string>


// Sets default values for this component's properties
UPositionReporterRock::UPositionReporterRock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporterRock::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Position Report Reporting for Duty on Rock"));
    auto objName = this->GetName();
    auto strName = objName.GetCharArray();
	
}


// Called every frame
void UPositionReporterRock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

