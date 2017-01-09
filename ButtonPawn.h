// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ButtonHUD.h"
#include "ButtonPawn.generated.h"

/// note to self templates are def inline and there for cant see the cpp
template<typename T>
class ButtonBinding
{
private:
	T* Source;
	FName HumanName;
	void (T::*pfBindedFunc)();
public:

	ButtonBinding()
	{
		Source = nullptr;
		pfBindedFunc = nullptr;
		bNeedsTick = false;
		HumanName = "";
	};

	ButtonBinding(T* nSource, void (T::*npfBindedFunc)(), FName nHumanName)
	{
		Source = nSource;
		pfBindedFunc = npfBindedFunc;
		HumanName = nHumanName;
	};

	void CallFunction(FName inHumanName)
	{
		if (Source != nullptr && pfBindedFunc != nullptr && HumanName == inHumanName)
				(Source->*pfBindedFunc)();
	};

};

UCLASS()
class IRONSOLIDUS_API AButtonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AButtonPawn();

	float MenuSenc;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Menu Related calls / vars
//private:
	UPROPERTY()
	bool bIsMenuOpen;

	UPROPERTY()
	FVector2D Currsor;

	UPROPERTY()
	int32 Button;

	UPROPERTY()
	int32 HoverTime;

	UPROPERTY()
	bool bCheck;

	UPROPERTY()
	TArray<int32> MenuStack;

	UPROPERTY()
	AButtonHUD* HUD;

	bool checkMouseBounds(FMenu MBounds);

	bool checkMouseBounds(FButton BBounds);

	void CheckMouse();

	UFUNCTION()
	void MoveMouseX(float Delta);

	UFUNCTION()
	void MoveMouseY(float Delta);

	UFUNCTION()
	void ToggleMenu();

	//this will tell su if it has worked the inish setup
	UPROPERTY()
	bool bHasInishHUD;
};
