// Fill out your copyright notice in the Description page of Project Settings.

#include "IronSolidus3.h"
#include "TestButtonHUD.h"

ATestButtonHUD::ATestButtonHUD(const FObjectInitializer& PCIP) : Super(PCIP)
{
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> Texture(TEXT("Texture2D'/Game/HUD_Assets/Builderhud1.Builderhud1'"));
	TheTemplate = Texture.Object;

	//static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("Texture2D'/Game/HUD_Assets/Builderhud1.Builderhud1'"));
	//TheFont = Font.Object;

	CursVish = FCanvasIcon(UCanvas::MakeIcon(TheTemplate, 360, 143, 34, 24));

	TArray<FButton> Button;
	FMenu Menu;
	Button.Add(MakeButton(0.0f, 200.0f, 200.0f, 560.0f, UCanvas::MakeIcon(TheTemplate, 360, 0, 303, 140), UCanvas::MakeIcon(TheTemplate, 362, 0, 300, 140), "Test Button 2", "this button is for testing"));
	Button.Add(MakeButton(0.0f, 200.0f, 400.0f, 560.0f, UCanvas::MakeIcon(TheTemplate, 360, 0, 303, 140), UCanvas::MakeIcon(TheTemplate, 0, 0, 1, 1), "Test Button", "this button is for testing"));
	Menu = MakeMenu(0.0f, 0.0f, 533.33333333333333333333333333333f, 900.0f, UCanvas::MakeIcon(TheTemplate, 0, 0, 345, 1024), Button, 1);
	Menus.Add(Menu);
	Button.Empty();
	
}