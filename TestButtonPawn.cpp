// Fill out your copyright notice in the Description page of Project Settings.

#include "IronSolidus3.h"
#include "TestButtonPawn.h"

ATestButtonPawn::ATestButtonPawn()
	:Super()
{
	//this works now
	ButtonBinding<ATestButtonPawn> NBB = ButtonBinding<ATestButtonPawn>(this, &ATestButtonPawn::TestMenuAction, "Test Button");
	ButtonBindings.Add(NBB);
}


void ATestButtonPawn::TestMenuAction()
{
	if (GEngine != nullptr)
	{
		GEngine->bEnableOnScreenDebugMessages = true;
		GEngine->bEnableOnScreenDebugMessagesDisplay = true;
		GEngine->AddOnScreenDebugMessage(-1, 5000.f, FColor::Yellow, TEXT("You have pressed the test button. Congrads! If you are reading this it works"));

	}
		
}


void ATestButtonPawn::ClickMouse()
{
	if (HUD != nullptr && Button > -1)
	{
		HUD->SetButtonState(Button, 3);
		for (int8 i = 0; i < ButtonBindings.Num(); i++)
			ButtonBindings[i].CallFunction(HUD->GetButton(Button).Name);
	}
}


void ATestButtonPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &ATestButtonPawn::ClickMouse);
}
