// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/HUD.h"
#include "ButtonHUD.generated.h"


USTRUCT()
struct FButton
{
	GENERATED_USTRUCT_BODY()

	enum ButtonState
	{
		Basic,
		Hover,
		Pressed
	};
	
	ButtonState ButtonsState;
	FVector2D Start, End, Width;

	bool NeedsTick;
	int16 Timer;
	FName Name;
	FString ToolTip;

	FCanvasIcon VisualUp, VisualDown;

	void Tick(float Delta);
};

USTRUCT()
struct FMenu
{
	GENERATED_USTRUCT_BODY()
		  
	enum MenuButtonTypes
	{ 
		FollowingButtons,
		fixedButton
	};

	MenuButtonTypes ButtonTypes;

	FVector2D Start, End, Width;

	FCanvasIcon Visual;

	TArray<FButton> TheButtons;

	void MoveMenu(FVector2D Move);
};


/**
 * 
 */
UCLASS()
class IRONSOLIDUS_API AButtonHUD : public AHUD
{
	GENERATED_BODY()

public:
		AButtonHUD(const FObjectInitializer& PCIP);

//private:
	//menu var to use
		UPROPERTY()
		bool bIsMenuUp;

		UPROPERTY()
		TArray<int32> MenuDrawStack;

		TArray<FButton*> ButtonTicks;

		UPROPERTY()
		UFont* TheFont;

		UPROPERTY()
		UTexture2D* TheTemplate;

		UPROPERTY()
		TArray<FMenu> Menus;

		UPROPERTY()
		FVector2D ScreenScale;

		UPROPERTY()
		FCanvasIcon CursVish;

		UPROPERTY()
		FVector2D CursLoc;
		UPROPERTY()
		float CursScale;

		// the menu creation tools
		// this one makes a menu from the points at the corrners
		UFUNCTION()
		FMenu MakeMenu(float XStart, float YStart, float XEnd, float YEnd, FCanvasIcon Visuala, TArray<FButton> Buttons, int32 ButtonTypes);

		// this one makes a button from the points at the corrners
		UFUNCTION()
		FButton MakeButton(float XStart, float YStart, float XEnd, float YEnd, FCanvasIcon Visualup, FCanvasIcon Visualdown, FName name, FString toolTip);

	// the draw calls
		// draws from a stack of ints
		void DrawMenuStack();

		// draws a single button at a fixed spot
		void DrawButton(FButton button);

		// draw a menu with fixed buttons
		void DrawMenu(FMenu Menu);

		// draw a menu with Buttons in Realtion to Menu
		void DrawMenuBRM(FMenu Menu);

		// draws the complete stack
		void DrawMenus();

		// main draw loop
		virtual void DrawHUD() override;

		/** after all game elements are created */
		virtual void PostInitializeComponents() override;

public:
		//Pawn utillity calls
		// Get gets your full list
		UFUNCTION()
		TArray<int32> GetStackMenus();

		UFUNCTION()
		TArray<FMenu> GetMenus();

		// Gets a menu
		UFUNCTION()
		FMenu GetMenu(int32 Index);

		// Gets a single button
		UFUNCTION()
		FButton GetButtonMenu(int32 MIndex, int32 BIndex);

		UFUNCTION()
		FButton GetButton(int32 BIndex);

		// Sets the currsor location
		UFUNCTION()
		void SetTheCurrsor(const FVector2D &curssLoc);

		// Sets the button state (ToState -> FButton::ButtonState : 1 == Basic, 2 == Hover, 3 == Pressed)
		UFUNCTION()
		void SetButtonStateMenu(int32 MIndex, int32 BIndex, int8 ToState);

		UFUNCTION()
		void SetButtonState(int32 BIndex, int8 ToState);

		UFUNCTION()
		void SetMenuStack(TArray<int32> NewStack);

		UFUNCTION()
		void OpenMenu();

		UFUNCTION()
		void CloseMenu();

		void Tick(float DeltaTime);

	//moves the menue
		void MoveMenu(int MenuNumber, FVector2D Move);

		FVector2D GetScreenScale();

};
