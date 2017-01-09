// Fill out your copyright notice in the Description page of Project Settings.

#include "IronSolidus3.h"
#include "MechaPartComponent.h"


// Sets default values for this component's properties
UMechaPartComponent::UMechaPartComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMechaPartComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	// ...
	
}


// Called every frame
void UMechaPartComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}


void UMechaPartComponent::AttachPart(UMechaPartComponent* theParent, int8 theParentSocket, int8 TheChildSocket)
{
	FRotator SetTo, dummy;
	if (this->DoesSocketExist("PartsSocket" + theParentSocket))
	{
		theParent->AttachTo(theParent, "PartsSocket" + theParentSocket);
		ParentsSocketNumber = theParentSocket;
	}

	if (this->DoesSocketExist("PartsSocket" + TheChildSocket))
	{
		(FRotator(180.0f, 180.0f, 180.0f) + theParent->GetSocketRotation("PartsSocket" + theParentSocket) - GetSocketRotation("PartsSocket" + TheChildSocket)).GetWindingAndRemainder(dummy, SetTo);
		SetRelativeRotation(SetTo);
		SetRelativeLocation(theParent->GetSocketLocation("PartsSocket" + theParentSocket) + GetSocketLocation("PartsSocket" + TheChildSocket));
	}
} 


void UMechaPartComponent::DamagePart(AActor* Source, float Damage)
{
}