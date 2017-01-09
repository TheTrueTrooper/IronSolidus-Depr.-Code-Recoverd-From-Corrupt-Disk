// Fill out your copyright notice in the Description page of Project Settings.

#include "IronSolidus3.h"
#include "ButtonHUD.h"

void FButton::Tick(float Delta)
{
	Timer = Timer++;
	if (Timer > 20)
	{
		Timer = 0;
		ButtonsState = ButtonState::Basic;
		NeedsTick = false;
	}
}

void FMenu::MoveMenu(FVector2D Move)
{
	Start = Start + Move;
	End = End + Move;
}

FButton AButtonHUD::MakeButton(float XStart, float YStart, float XEnd, float YEnd, FCanvasIcon Visualup, FCanvasIcon Visualdown, FName name, FString toolTip)
{

	FButton NewButton;

	NewButton.Start.X = XStart;
	NewButton.Start.Y = YStart;
	NewButton.End.X = XEnd;
	NewButton.End.Y = YEnd;

	NewButton.Width.X = XEnd - XStart;
	NewButton.Width.Y = XEnd - YStart;

	NewButton.VisualUp = Visualup;
	NewButton.VisualDown = Visualdown;

	NewButton.Name = name;
	NewButton.ToolTip = toolTip;
	
	return NewButton;
}




FMenu AButtonHUD::MakeMenu(float XStart, float YStart, float XEnd, float YEnd, FCanvasIcon Visuala, TArray<FButton> Buttons, int32 ButtonTypes = 1)
{
	FMenu NewMenu;

	NewMenu.Start.X = XStart;
	NewMenu.Start.Y = YStart;
	NewMenu.End.X = XEnd;
	NewMenu.End.Y = YEnd;

	NewMenu.Width.X = XEnd - XStart;
	NewMenu.Width.Y = XEnd - XStart;

	NewMenu.Visual = Visuala;

	NewMenu.TheButtons = Buttons;

	if (ButtonTypes == 1)
		NewMenu.ButtonTypes = NewMenu.FollowingButtons;

	if (ButtonTypes == 2)
		NewMenu.ButtonTypes = NewMenu.fixedButton;
	
	return NewMenu;
}


void AButtonHUD::DrawHUD()
{
	Super::DrawHUD();
	if (bIsMenuUp)
	{
		DrawMenuStack();
	}
}


void AButtonHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}


AButtonHUD::AButtonHUD(const FObjectInitializer& PCIP) : Super(PCIP)
{
	CursScale = 1;
	bIsMenuUp = false;

}


void AButtonHUD::DrawButton(FButton button)
{
	if (Canvas == nullptr)
		return;
	FVector2D Size;

	FCanvasTileItem RectItem(ScreenScale * FVector2D(CursLoc.X - 5, CursLoc.Y - 5), ScreenScale * FVector2D(Size.X + 5, Size.Y + 5), FColor(255, 255, 255, 100));
	FCanvasLineItem Line1(ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5)), ScreenScale * (FVector2D(CursLoc.X - 5, 0) + FVector2D(Size.X + 5, CursLoc.Y - 5)));
	FCanvasLineItem Line2(ScreenScale * (FVector2D(CursLoc.X - 5, 0) + FVector2D(Size.X + 5, CursLoc.Y - 5)), ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5) + FVector2D(Size.X + 5, Size.Y + 5)));
	FCanvasLineItem Line3(ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5) + FVector2D(Size.X + 5, Size.Y + 5)), ScreenScale * (FVector2D(0, CursLoc.Y - 5) + FVector2D(CursLoc.X - 5, Size.Y + 5)));
	FCanvasLineItem Line4(ScreenScale * (FVector2D(0, CursLoc.Y - 5) + FVector2D(CursLoc.X - 5, Size.Y + 5)), ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5)));

	switch (button.ButtonsState)
	{
	case FButton::Basic:
		Canvas->DrawTile(button.VisualUp.Texture, ScreenScale.X * button.Start.X, ScreenScale.Y * button.Start.Y, ScreenScale.X * (button.End.X- button.Start.X), ScreenScale.Y * (button.End.X - button.Start.X), button.VisualUp.U, button.VisualUp.V, button.VisualUp.UL, button.VisualUp.VL);
		Canvas->TextSize(TheFont, button.Name.ToString(), Size.X, Size.Y, ScreenScale.X , ScreenScale.Y );
		Canvas->DrawText(TheFont, button.Name.ToString(), ScreenScale.X * (button.Start.X + (button.Width.X - Size.X) / 2), ScreenScale.Y * (button.Start.Y + (button.Width.Y - Size.Y) / 2), ScreenScale.X , ScreenScale.Y);
		break;
	case FButton::Hover:
		Canvas->DrawTile(button.VisualUp.Texture, ScreenScale.X * button.Start.X, ScreenScale.Y * button.Start.Y, ScreenScale.X * (button.End.X - button.Start.X), ScreenScale.Y * (button.End.X - button.Start.X), button.VisualUp.U, button.VisualUp.V, button.VisualUp.UL, button.VisualUp.VL);
		Canvas->TextSize(TheFont, button.Name.ToString(), Size.X, Size.Y, ScreenScale.X, ScreenScale.X);
		Canvas->DrawText(TheFont, button.Name.ToString(), ScreenScale.X * (button.Start.X + (button.Width.X - Size.X) / 2), ScreenScale.Y * (button.Start.Y + (button.Width.Y - Size.Y) / 2), ScreenScale.X, ScreenScale.Y);
		Canvas->TextSize(TheFont, button.ToolTip, Size.X, Size.Y, 1.0f, 1.0f);
		Line1.SetColor(FColor(0, 0, 0, 255));
		Line2.SetColor(FColor(0, 0, 0, 255));
		Line3.SetColor(FColor(0, 0, 0, 255));
		Line4.SetColor(FColor(0, 0, 0, 255));
		Canvas->DrawItem(RectItem);
		Canvas->DrawItem(Line1);
		Canvas->DrawItem(Line2);
		Canvas->DrawItem(Line3);
		Canvas->DrawItem(Line4);
		Canvas->DrawText(TheFont, button.ToolTip, ScreenScale.X * CursLoc.X, ScreenScale.Y * CursLoc.Y, ScreenScale.X, ScreenScale.Y);
		break;
	case FButton::Pressed:
		Canvas->DrawTile(button.VisualUp.Texture, ScreenScale.X * button.Start.X, ScreenScale.Y * button.Start.Y, ScreenScale.X * (button.End.X - button.Start.X), ScreenScale.Y * (button.End.X - button.Start.X), button.VisualUp.U, button.VisualUp.V, button.VisualUp.UL, button.VisualUp.VL);
		Canvas->TextSize(TheFont, button.Name.ToString(), Size.X, Size.Y, ScreenScale.X, ScreenScale.Y);
		Canvas->DrawText(TheFont, button.Name.ToString(), ScreenScale.X * (button.Start.X + (button.Width.X - Size.X) / 2), ScreenScale.X * (button.Start.Y + (button.Width.Y - Size.Y) / 2), ScreenScale.X, ScreenScale.Y);
		break;
	}
	Canvas->DrawIcon(CursVish, CursLoc.X * ScreenScale.X, CursLoc.Y * ScreenScale.Y, 20);
}



void AButtonHUD::DrawMenuBRM(FMenu Menu)
{
	if (Canvas == nullptr)
		return;
	//GetWorld()->GetGameViewport()->GetViewportSize(ScreenScale);
	//ScreenScale.X /= 1600;
	//ScreenScale.Y /= 900;
	ScreenScale.X = Canvas->ClipX / 1600;
	ScreenScale.Y = Canvas->ClipY / 900;


	FVector2D Size;

	FCanvasTileItem RectItem((FVector2D(0, 0)),FVector2D(1, 1), FColor(255, 255, 255, 100));
	FCanvasLineItem Line1((FVector2D(0, 0)), FVector2D(1, 1));


	Canvas->DrawTile(Menu.Visual.Texture, ScreenScale.X * Menu.Start.X, ScreenScale.Y * Menu.Start.Y, ScreenScale.X * (Menu.End.X - Menu.Start.X), ScreenScale.Y * (Menu.End.Y - Menu.Start.Y), Menu.Visual.U, Menu.Visual.V, Menu.Visual.UL, Menu.Visual.VL);


	for (int32 i = 0; i < Menu.TheButtons.Num(); i++)
	{

		switch (Menu.TheButtons[i].ButtonsState)
		{
		case FButton::Basic:
			Canvas->DrawTile(Menu.TheButtons[i].VisualUp.Texture, ScreenScale.X *  Menu.TheButtons[i].Start.X, ScreenScale.Y * Menu.TheButtons[i].Start.Y, ScreenScale.X * ( Menu.TheButtons[i].End.X - Menu.TheButtons[i].Start.X), ScreenScale.Y * ( Menu.TheButtons[i].End.Y - Menu.TheButtons[i].Start.Y), Menu.TheButtons[i].VisualUp.U, Menu.TheButtons[i].VisualUp.V, Menu.TheButtons[i].VisualUp.UL, Menu.TheButtons[i].VisualUp.VL);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].Name.ToString(), Size.X, Size.Y, 20.0f * ScreenScale.X, 20.0f * ScreenScale.Y);
			Canvas->DrawText(TheFont, Menu.TheButtons[i].Name.ToString(), ScreenScale.X * (Menu.Start.X + Menu.TheButtons[i].Start.X + (Menu.TheButtons[i].Width.X - Size.X) / 2), ScreenScale.X * (Menu.Start.Y + Menu.TheButtons[i].Start.Y + (Menu.TheButtons[i].Width.Y - Size.Y) / 2), ScreenScale.X, ScreenScale.Y);
			break;
		case FButton::Hover:
			Canvas->DrawTile(Menu.TheButtons[i].VisualUp.Texture, ScreenScale.X *  Menu.TheButtons[i].Start.X, ScreenScale.Y * Menu.TheButtons[i].Start.Y, ScreenScale.X * (Menu.TheButtons[i].End.X - Menu.TheButtons[i].Start.X), ScreenScale.Y * (Menu.TheButtons[i].End.Y - Menu.TheButtons[i].Start.Y), Menu.TheButtons[i].VisualUp.U, Menu.TheButtons[i].VisualUp.V, Menu.TheButtons[i].VisualUp.UL, Menu.TheButtons[i].VisualUp.VL);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].Name.ToString(), Size.X, Size.Y, 20.0f * ScreenScale.X, 20.0f * ScreenScale.Y);
			Canvas->DrawTile(Menu.TheButtons[i].VisualUp.Texture, ScreenScale.X *  Menu.TheButtons[i].Start.X, ScreenScale.Y * Menu.TheButtons[i].Start.Y, ScreenScale.X * ( Menu.TheButtons[i].End.X - Menu.TheButtons[i].Start.X), ScreenScale.Y * ( Menu.TheButtons[i].End.Y - Menu.TheButtons[i].Start.Y), Menu.TheButtons[i].VisualUp.U, Menu.TheButtons[i].VisualUp.V, Menu.TheButtons[i].VisualUp.UL, Menu.TheButtons[i].VisualUp.VL);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].ToolTip, Size.X, Size.Y, 20.0f * ScreenScale.X, 20.0f * ScreenScale.Y);
			Line1.SetColor(FColor(0, 0, 0, 255));
			RectItem.Position = CursLoc;
			RectItem.Size = Size + 10;
			Canvas->DrawItem(RectItem);
			Line1.LineThickness = 3;
			Line1.Position = ScreenScale.X * CursLoc;
			Line1.SetEndPos( ScreenScale.X * FVector2D(CursLoc.X + Size.X + 10, CursLoc.Y));
			Canvas->DrawItem(Line1);
			Line1.Position = ScreenScale.X * FVector2D(CursLoc.X, CursLoc.Y + Size.Y + 10);
			Line1.SetEndPos( ScreenScale.X * FVector2D(CursLoc.X + Size.X + 5, CursLoc.Y + Size.Y + 10));
			Canvas->DrawItem(Line1);
			Line1.Position = ScreenScale.X * FVector2D(CursLoc.X + Size.X + 5, CursLoc.Y);
			Line1.SetEndPos( ScreenScale.X * FVector2D(CursLoc.X + Size.X + 10, CursLoc.Y + Size.Y + 10));
			Canvas->DrawItem(Line1);
			Line1.Position = ScreenScale.X * CursLoc;
			Line1.SetEndPos(ScreenScale.X * FVector2D(CursLoc.X, CursLoc.Y + Size.Y + 10));
			Canvas->DrawItem(Line1);
			Canvas->DrawText(TheFont, Menu.TheButtons[i].ToolTip, ScreenScale.X * (CursLoc.X + 5), 20.0f * ScreenScale.X, 20.0f * ScreenScale.Y);
			break;
		case FButton::Pressed:
			Canvas->DrawTile(Menu.TheButtons[i].VisualDown.Texture, ScreenScale.X * (Menu.Start.X + Menu.TheButtons[i].Start.X), ScreenScale.Y * (Menu.Start.Y + Menu.TheButtons[i].Start.Y), ScreenScale.X * (Menu.Start.X + Menu.TheButtons[i].End.X - Menu.TheButtons[i].Start.X), ScreenScale.Y * (Menu.Start.Y + Menu.TheButtons[i].End.Y - Menu.TheButtons[i].Start.Y), Menu.TheButtons[i].VisualDown.U, Menu.TheButtons[i].VisualDown.V, Menu.TheButtons[i].VisualDown.UL, Menu.TheButtons[i].VisualDown.VL);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].Name.ToString(), Size.X, Size.Y, 1.0f, 1.0f);
			Canvas->DrawText(TheFont, Menu.TheButtons[i].Name.ToString(), ScreenScale.X * (Menu.Start.X + Menu.TheButtons[i].Start.X + (Menu.TheButtons[i].Width.X - Size.X) / 2), ScreenScale.X * (Menu.Start.Y + Menu.TheButtons[i].Start.Y + (Menu.TheButtons[i].Width.Y - Size.Y) / 2), ScreenScale.X, ScreenScale.Y);
			break;
		}
	}
	Canvas->DrawIcon(CursVish, CursLoc.X * ScreenScale.X, CursLoc.Y * ScreenScale.Y, CursScale * (ScreenScale.Y + ScreenScale.X)/2);
}


void AButtonHUD::DrawMenu(FMenu Menu)
{
	if (Canvas == nullptr)
		return;
	
	ScreenScale.X = Canvas->ClipX / 1600;
	ScreenScale.Y = Canvas->ClipY / 900;

	FVector2D Size;

	FCanvasTileItem RectItem(ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5)), ScreenScale * (FVector2D(Size.X + 5, Size.Y + 5)), FColor(255, 255, 255, 100));
	FCanvasLineItem Line1(ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5)), ScreenScale * (FVector2D(CursLoc.X - 5, 0) + FVector2D(Size.X + 5, CursLoc.Y - 5)));
	FCanvasLineItem Line2(ScreenScale * (FVector2D(CursLoc.X - 5, 0) + FVector2D(Size.X + 5, CursLoc.Y - 5)), ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5) + FVector2D(Size.X + 5, Size.Y + 5)));
	FCanvasLineItem Line3(ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5) + FVector2D(Size.X + 5, Size.Y + 5)), ScreenScale * (FVector2D(0, CursLoc.Y - 5) + FVector2D(CursLoc.X - 5, Size.Y + 5)));
	FCanvasLineItem Line4(ScreenScale * (FVector2D(0, CursLoc.Y - 5) + FVector2D(CursLoc.X - 5, Size.Y + 5)), ScreenScale * (FVector2D(CursLoc.X - 5, CursLoc.Y - 5)));


	Canvas->DrawTile(Menu.Visual.Texture, Menu.Start.X, Menu.Start.Y, Menu.Width.X, Menu.Width.Y, Menu.Visual.U, Menu.Visual.V, Menu.Visual.UL, Menu.Visual.VL);

	for (int32 i = 0; i < Menu.TheButtons.Num(); i++)
	{
		switch (Menu.TheButtons[i].ButtonsState)
		{
		case FButton::Basic:
			Canvas->DrawTile(Menu.TheButtons[i].VisualUp.Texture, ScreenScale.X * Menu.TheButtons[i].Start.X, ScreenScale.Y * Menu.TheButtons[i].Start.Y, ScreenScale.X * Menu.TheButtons[i].Width.X, ScreenScale.Y * Menu.TheButtons[i].Width.Y, Menu.TheButtons[i].VisualUp.U, Menu.TheButtons[i].VisualUp.V, Menu.TheButtons[i].VisualUp.UL, Menu.TheButtons[i].VisualUp.VL);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].Name.ToString(), Size.X, Size.Y, 1.0f, 1.0f);
			Canvas->DrawText(TheFont, Menu.TheButtons[i].Name.ToString(), ScreenScale.X * (Menu.TheButtons[i].Start.X + (Menu.TheButtons[i].Width.X - Size.X) / 2), ScreenScale.Y * (Menu.TheButtons[i].Start.Y + (Menu.TheButtons[i].Width.Y - Size.Y) / 2), ScreenScale.X, ScreenScale.Y);
			break;
		case FButton::Hover:
			Canvas->DrawTile(Menu.TheButtons[i].VisualUp.Texture, ScreenScale.X * Menu.TheButtons[i].Start.X, ScreenScale.Y * Menu.TheButtons[i].Start.Y, ScreenScale.X * Menu.TheButtons[i].Width.X, ScreenScale.Y * Menu.TheButtons[i].Width.Y, Menu.TheButtons[i].VisualUp.U, Menu.TheButtons[i].VisualUp.V, Menu.TheButtons[i].VisualUp.UL, Menu.TheButtons[i].VisualUp.VL);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].Name.ToString(), Size.X, Size.Y, 1.0f, 1.0f);
			Canvas->DrawText(TheFont, Menu.TheButtons[i].Name.ToString(), ScreenScale.X * (Menu.TheButtons[i].Start.X + (Menu.TheButtons[i].Width.X - Size.X) / 2), ScreenScale.Y * (Menu.TheButtons[i].Start.Y + (Menu.TheButtons[i].Width.Y - Size.Y) / 2), ScreenScale.X, ScreenScale.Y);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].ToolTip, Size.X, Size.Y, 1.0f, 1.0f);
			Line1.SetColor(FColor(0, 0, 0, 255));
			Line2.SetColor(FColor(0, 0, 0, 255));
			Line3.SetColor(FColor(0, 0, 0, 255));
			Line4.SetColor(FColor(0, 0, 0, 255));
			Canvas->DrawItem(RectItem);
			Canvas->DrawItem(Line1);
			Canvas->DrawItem(Line2);
			Canvas->DrawItem(Line3);
			Canvas->DrawItem(Line4);
			Canvas->DrawText(TheFont, Menu.TheButtons[i].ToolTip, ScreenScale.X * CursLoc.X, ScreenScale.Y *CursLoc.Y, ScreenScale.X, ScreenScale.Y);
			break;
		case FButton::Pressed:
			Canvas->DrawTile(Menu.TheButtons[i].VisualDown.Texture, ScreenScale.X * Menu.TheButtons[i].Start.X, ScreenScale.X * Menu.TheButtons[i].Start.Y, ScreenScale.X * Menu.TheButtons[i].Width.X, ScreenScale.Y * Menu.TheButtons[i].Width.Y, Menu.TheButtons[i].VisualDown.U, Menu.TheButtons[i].VisualDown.V, Menu.TheButtons[i].VisualDown.UL, Menu.TheButtons[i].VisualDown.VL);
			Canvas->TextSize(TheFont, Menu.TheButtons[i].Name.ToString(), Size.X, Size.Y, 1.0f, 1.0f);
			Canvas->DrawText(TheFont, Menu.TheButtons[i].Name.ToString(), ScreenScale.X * (Menu.TheButtons[i].Start.X + (Menu.TheButtons[i].Width.X - Size.X) / 2), ScreenScale.X * (Menu.TheButtons[i].Start.Y + (Menu.TheButtons[i].Width.Y - Size.Y)) / 2, ScreenScale.X, ScreenScale.Y);
			break;
		}

	}
	Canvas->DrawIcon(CursVish, CursLoc.X * ScreenScale.X, CursLoc.Y * ScreenScale.X);
}

void AButtonHUD::DrawMenuStack()
{
	for (int32 i = 0; i < MenuDrawStack.Num(); i++)
	{
		DrawMenuBRM(Menus[MenuDrawStack[i]]);
	}
}


TArray<FMenu> AButtonHUD::GetMenus()
{
	return Menus;
}


FMenu AButtonHUD::GetMenu(int32 Index)
{
	return Menus[Index];
}


FButton AButtonHUD::GetButtonMenu(int32 MIndex, int32 BIndex)
{
	return Menus[MIndex].TheButtons[BIndex];
}

FButton AButtonHUD::GetButton(int32 BIndex)
{
	return Menus[Menus.Num() -1].TheButtons[BIndex];
}



void AButtonHUD::SetTheCurrsor(const FVector2D &curssLoc)
{
	CursLoc = curssLoc;
}

// Sets the button state (ToState -> FButton::ButtonState : 1 == Basic, 2 == Hover, 3 == Pressed)
void AButtonHUD::SetButtonStateMenu(int32 MIndex, int32 BIndex, int8 ToState)
{
	if (BIndex > -1)
	if (Menus[MIndex].TheButtons[BIndex].ButtonsState != Menus[MIndex].TheButtons[BIndex].Pressed)
	{
		if (ToState == 1)
			Menus[MIndex].TheButtons[BIndex].ButtonsState = Menus[MIndex].TheButtons[BIndex].Basic;
		else if (ToState == 2)
			Menus[MIndex].TheButtons[BIndex].ButtonsState = Menus[MIndex].TheButtons[BIndex].Hover;
		else if (ToState == 3)
		{
			Menus[MIndex].TheButtons[BIndex].ButtonsState = Menus[MIndex].TheButtons[BIndex].Pressed;
			Menus[MIndex].TheButtons[BIndex].NeedsTick = true;
			ButtonTicks.Add(&Menus[MIndex].TheButtons[BIndex]);
		}
	}
}

void AButtonHUD::SetButtonState(int32 BIndex, int8 ToState)
{
	if (BIndex > -1)
	if (Menus[Menus.Num() - 1].TheButtons[BIndex].ButtonsState != FButton::Pressed)
	{
		if (ToState == 1)
			Menus[Menus.Num() - 1].TheButtons[BIndex].ButtonsState = FButton::Basic;
		else if (ToState == 2)
			Menus[Menus.Num() - 1].TheButtons[BIndex].ButtonsState = FButton::Hover;
		else if (ToState == 3)
		{
			Menus[Menus.Num() - 1].TheButtons[BIndex].ButtonsState = FButton::Pressed;
			Menus[Menus.Num() - 1].TheButtons[BIndex].NeedsTick = true;
			ButtonTicks.Add(&Menus[Menus.Num() - 1].TheButtons[BIndex]);
		}
	}
}


TArray<int32> AButtonHUD::GetStackMenus()
{
	return MenuDrawStack;
}


void AButtonHUD::SetMenuStack(TArray<int32> NewStack)
{
	MenuDrawStack = NewStack;
}

void AButtonHUD::Tick(float DeltaTime)
{
Super::Tick(DeltaTime);
	for (int32 i = 0; i < ButtonTicks.Num(); i++)
	{
		if (ButtonTicks[i] != nullptr)
		{
			if (ButtonTicks[i]->NeedsTick)
			{
				ButtonTicks[i]->Tick(DeltaTime);
			}
			else
			{
				ButtonTicks.RemoveAt(i);
			}
		}
		else
		{
			ButtonTicks.RemoveAt(i);
		}
	}
}

void AButtonHUD::MoveMenu(int MenuNumber, FVector2D Move)
{
	Menus[MenuNumber].MoveMenu(Move);
}

FVector2D AButtonHUD::GetScreenScale()
{
	return ScreenScale;
}

void AButtonHUD::OpenMenu()
{
	bIsMenuUp = true;
}

void AButtonHUD::CloseMenu()
{
	bIsMenuUp = false;
}
