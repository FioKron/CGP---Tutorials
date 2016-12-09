#pragma once

// Bespoke:
#include "Monster.h"

// For Windows:
#include<stdio.h>

// For SDL:
#include "SDL.h"

// In order to use vector:
#include <vector>

/** 
	(From the 3rd tutorial)
	'Foward declared structs, for the Game class to use (a promise to the compiler)'
*/
struct SDL_Window;
struct SDL_Renderer;

// Foward declaration of classes, required in this game:
//class Bitmap; // (Tutorial 4, Exercise 1): '04-01'

class Game
{

private:

	// Properties:

	/** 
		For SDL to use
	*/
	SDL_Window*		M_Window;
	SDL_Renderer*	M_Renderer;

	// Flags:
	bool M_Running;

	// Bitmaps:
	//Bitmap*			M_Monster; // '04-01'
	//Bitmap*			M_MonsterWithTransparency; // '04-01'
	//Bitmap*			M_MonsterWithTransparencyThatHasKey; // '04-01'
	
	/** To contain all monsters in the game */
	std::vector<Bitmap*> MonsterCollection;


	// Functions:

	/**
		Clear and present the renderer as required
	*/
	void ClearRenderer();
	void PresentRenderer();

	/**
		Wait for a certain quantity of time

		@Param: Uint32 Milliseconds: The time (in milliseconds) to wait for
	*/
	void Delay(Uint32 Milliseconds);

	/** Check for any events */
	void CheckEvents();

public:
	/**
		Public functions
	*/
	Game();
	~Game();
	
	/**
		Description: Set the colour of the display

		@Params:

		Uint8 Red: Red colour component.
		Uint8 Green: Green colour component.
		Uint8 Blue: Blue colour component.
		Uint8 Alpha: Alpha component for the transparency level of the RGB components
	*/
	void SetDisplayColour(Uint8 Red, Uint8 Blue, Uint8 Green, Uint8 Alpha);

	/**
		Description: For updating the game
	*/
	void Update();
};

