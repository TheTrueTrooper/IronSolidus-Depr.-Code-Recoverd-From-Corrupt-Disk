// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ButtonPawn.h"
#include "TestButtonPawn.generated.h"

/**
 * 
 */
UCLASS()
class IRONSOLIDUS3_API ATestButtonPawn : public AButtonPawn
{
	GENERATED_BODY()
		 
	TArray<ButtonBinding<ATestButtonPawn>> ButtonBindings;

	void TestMenuAction();

	void ClickMouse();
	
	ATestButtonPawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
