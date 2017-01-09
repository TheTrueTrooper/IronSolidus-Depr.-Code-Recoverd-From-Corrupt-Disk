// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ButtonPawn.h"
#include "MechaPartComponent.h"
#include "MechcaPawn.generated.h"

/**
 * 
 */
UCLASS()
class IRONSOLIDUS_API AMechcaPawn : public AButtonPawn
{
	GENERATED_BODY()

	enum SocketSelecter
	{
		Parent,
		Child
	};

	enum State
	{
		defualt,
		AddingPart,
		Rotate,
		Editing,
		options,
		buy,
		sell
	};

	struct AddableParts
	{
		UClass* CompClass;
		uint8 NumberOfParts;
	};

	State PawnsState;

	uint8 SelectedPart;

	uint8 SocketNumber;

	TArray<AddableParts> PartsToAdd;
	
	TArray<UMechaPartComponent*> PartsMasterList;

	TArray<ButtonBinding<AMechcaPawn>> ButtonBindings;

	void AddPart(uint8 PartNumToAdd, uint8 PartToAddTo, uint8 SocketToAddTo);

	void FlipPart(uint8 PartsIndex, uint8 SocketToAddTo);

	void SocketSelectUp();

	void SocketSelectDown();

	void PartSelectUp();

	void PartSelectDown();

	void ClickMouse();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
