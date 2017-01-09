// Fill out your copyright notice in the Description page of Project Settings.

#include "IronSolidus3.h"
#include "ButtonPawn.h"


// Sets default values
AButtonPawn::AButtonPawn()
{
	Button = -1;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MenuSenc = 5;

	bHasInishHUD = false;

}

// Called when the game starts or when spawned
void AButtonPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bHasInishHUD)
	{
		HUD = Cast<AButtonHUD>(Cast<APlayerController>(GetController())->GetHUD());
		if (HUD != nullptr)
		{
			Currsor.X = 1600 / 2;
			Currsor.Y = 900 / 2;
			HUD->SetTheCurrsor(Currsor);
			bHasInishHUD = true;
		}
	}

}

// Called every frame
void AButtonPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (!bHasInishHUD)
	{
		HUD = Cast<AButtonHUD>(Cast<APlayerController>(GetController())->GetHUD());
		if (HUD != nullptr)
		{
			Currsor.X = 1600 / 2;
			Currsor.Y = 900 / 2;
			HUD->SetTheCurrsor(Currsor);
			bHasInishHUD = true;
		}
	}
	CheckMouse(); // we must check our mouse every tick
}

// Called to bind functionality to input
void AButtonPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	// movement
	InputComponent->BindAxis("MouseX", this, &AButtonPawn::MoveMouseX);
	InputComponent->BindAxis("MouseY", this, &AButtonPawn::MoveMouseY);

	InputComponent->BindAction("MenuToggle", IE_Pressed, this, &AButtonPawn::ToggleMenu);
}

// called when the mouse is cicked

// Move mouse X input Call
void AButtonPawn::MoveMouseX(float Delta)
{
	if (bIsMenuOpen && (Delta > 0.4f || Delta < -0.4f))
	{
		Currsor.X = FMath::Clamp(Currsor.X + Delta * MenuSenc, 0.0f, 1600.0f);
		bCheck = true;
	}
}

// Move mouse y input Call
void AButtonPawn::MoveMouseY(float Delta)
{
	if (bIsMenuOpen && (Delta > 0.4f|| Delta < -0.4f))
	{
		Currsor.Y = FMath::Clamp(Currsor.Y - Delta * MenuSenc, 0.0f, 900.0f);
		bCheck = true;
	}
}

// checks the mouses location
void AButtonPawn::CheckMouse()
{
	// if we have moved
	if (bCheck)
	{
		// Remove all hovers if they are inplace
		HUD->SetButtonStateMenu(MenuStack[MenuStack.Num() - 1], Button, 1);
		// Set our huds currsor
		HUD->SetTheCurrsor(Currsor);
		// reset our hover timer
		HoverTime = 0;
		// if i less than zero its not set set it
		if (Button < 0)
		{
			for (int32 i = 0; i < HUD->GetMenu(MenuStack[MenuStack.Num() - 1]).TheButtons.Num(); i++)
			{
				if (checkMouseBounds(HUD->GetMenu(MenuStack[MenuStack.Num() - 1]).TheButtons[i]))// for each button we check the stack
				{
					Button = i;
				}
			}
		}
		// check to see if it is still on the spot first
		else if (!checkMouseBounds(HUD->GetMenu(MenuStack[MenuStack.Num() - 1]).TheButtons[Button]))
		{
			Button = -1;//if it isnt set it as unset
			for (int32 i = 0; i < HUD->GetMenu(MenuStack[MenuStack.Num() - 1]).TheButtons.Num(); i++)
			{
				if (checkMouseBounds(HUD->GetMenu(MenuStack[MenuStack.Num() - 1]).TheButtons[i]))// for each button we check the stack
				{
					Button = i;
				}
			}
		}
		bCheck = false; // when done prevent the loop from re firing till we move the mouse again and require it
	}
	else if (Button > -1 && HoverTime < 100) // also on the back side of this function if the button is set tick a hover time
	{ 
		HoverTime = FMath::Clamp(HoverTime++, 0, 100); // else count the ticks till 200
		if (HoverTime == 100) // if it hits 200 set a hover
			HUD->SetButtonStateMenu(MenuStack[MenuStack.Num() - 1], Button, 2);
	}
}

// these are quick functions to abstract away bound checking
bool AButtonPawn::checkMouseBounds(FMenu MBounds)
{
	if (Currsor.X > MBounds.Start.X && Currsor.X < MBounds.End.X && Currsor.Y > MBounds.Start.Y && Currsor.Y < MBounds.End.Y)
	return true; 
	else
	return false;
}


// these are quick functions to abstract away bound checking
bool AButtonPawn::checkMouseBounds(FButton BBounds)
{
	if ((Currsor.X > BBounds.Start.X && Currsor.X < BBounds.End.X) && (Currsor.Y > BBounds.Start.Y && Currsor.Y < BBounds.End.Y))
	return true;
	else
	return false;
}

void AButtonPawn::ToggleMenu()
{
	if (bHasInishHUD)
	{
		bIsMenuOpen = !bIsMenuOpen;
		if (HUD != nullptr)
		{
			if (bIsMenuOpen)
			{
				MenuStack.Empty(5);
				MenuStack.Add(0);
				HUD->SetMenuStack(MenuStack);
				HUD->OpenMenu();
			}
			else
				HUD->CloseMenu();
		}
	}
}
