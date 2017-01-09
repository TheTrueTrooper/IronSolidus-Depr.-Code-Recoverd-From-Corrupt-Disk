// Fill out your copyright notice in the Description page of Project Settings.

#include "IronSolidus3.h"
#include "MechcaPawn.h"


void AMechcaPawn::FlipPart(uint8 PartsIndex, uint8 SocketToAddTo)
{
	PartsMasterList[PartsIndex]->AttachPart(PartsMasterList[PartsIndex]->ParentPart, PartsMasterList[PartsIndex]->ParentsSocketNumber, SocketToAddTo);
	PartsMasterList.Last()->RegisterComponent();
}


void AMechcaPawn::AddPart(uint8 PartNumToAdd, uint8 PartToAddTo, uint8 SocketToAddTo)
{
	if (PartsToAdd[PartNumToAdd].NumberOfParts > 0)
	{
		 PartsMasterList.Add(ConstructObject<UMechaPartComponent>(PartsToAdd[PartNumToAdd].CompClass, this));
		 PartsMasterList.Last()->AttachPart(PartsMasterList[PartToAddTo], SocketToAddTo, 0);
		 PartsMasterList.Last()->RegisterComponent();
	}
}


void AMechcaPawn::SocketSelectUp()
{
	if (PartsMasterList[SelectedPart] != nullptr && PartsMasterList[SelectedPart]->DoesSocketExist("PartsSocket" + SocketNumber - 1))
		SocketNumber++;
}


void AMechcaPawn::SocketSelectDown()
{
	if (PartsMasterList[SelectedPart] != nullptr && PartsMasterList[SelectedPart]->DoesSocketExist("PartsSocket" + SocketNumber - 1))
		SocketNumber--;
}


void AMechcaPawn::PartSelectUp()
{
	if (PartsMasterList.Num() - 1 < SelectedPart)
	{
		SelectedPart++;
	}
}


void AMechcaPawn::PartSelectDown()
{
	if (0 > SelectedPart)
	{
		SelectedPart--;
	}
}


void AMechcaPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &AMechcaPawn::ClickMouse);
	InputComponent->BindAction("MouseClick", IE_Released, this, &AMechcaPawn::ClickMouse);
}

void AMechcaPawn::ClickMouse()
{
	if (HUD != nullptr && Button > -1)
	{
		HUD->SetButtonState(Button, 3);
		for (int8 i = 0; i < ButtonBindings.Num(); i++)
			ButtonBindings[i].CallFunction(HUD->GetButton(Button).Name);
	}
}
