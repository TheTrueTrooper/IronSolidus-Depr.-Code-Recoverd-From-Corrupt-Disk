// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "MechaPartComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IRONSOLIDUS_API UMechaPartComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// our children
	int8 NumberOfSockets; //(posible ChildNumber)
	TArray<UMechaPartComponent*> ChildParts;

	// our parts and its number
	UMechaPartComponent* ParentPart;
	int8 ParentsSocketNumber; 

	//materListNumbr
	int8 PartsNumber;

	// Sets default values for this component's properties
	UMechaPartComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY()
	USkeletalMeshComponent * PartsVish;
// these three may be case sencitive
	// the amount a part wieghs or for a base the amount a Base can hold
	UPROPERTY()
	float Wieght;

	// The amount of Power a part disipates or for a Gen it Generates
	UPROPERTY()
	float Power;

	//The heat a part creates or for a Gen or heat sink it can disipate
	UPROPERTY()
	float Heat;
//-----------------------
	// parts Damage it can take
	UPROPERTY()
	float health;

	// Parts Kinetic damage resistance
	UPROPERTY()
	float KArmor;

	// Parts Cemical damage resistance
	UPROPERTY()
	float CArmor;

	UPROPERTY()
	float BaseArmor;

	UFUNCTION()
	void AttachPart(UMechaPartComponent* theParent, int8 theParentSocket, int8 TheChildSocket);

	UFUNCTION()
	void DamagePart(AActor* Source, float Damage);
	
};
