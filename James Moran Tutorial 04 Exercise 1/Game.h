#pragma once

// For Windows:
#include <stdio.h>
#include <string> // '04-02'

// For SDL:
#include "SDL.h"
#include "SDL_ttf.h" // '04-02'

/** 
	(From the 3rd tutorial)
	'Foward declared structs, for the Game class to use (a promise to the compiler)'
*/
struct SDL_Window;
struct SDL_Renderer;

// Foward declaration of classes, required in this game:
class Bitmap; // (Tutorial 4, Exercise 1): '04-01'

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
	Bitmap*			M_Monster; // '04-01'
	Bitmap*			M_MonsterWithTransparency; // '04-01'
	Bitmap*			M_MonsterWithTransparencyThatHasKey; // '04-01'

	// Font:
	TTF_Font*		M_PSmallFont;	// '04-02'
	TTF_Font*		M_PLargeFont;	// '04-02'

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

	/** Handle Text: */
	void UpdateText(std::string Message, int XPosition, int YPosition, TTF_Font* FontStyle, 
		SDL_Color FontColour); // '04-02'

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

		@Params:

		int NewPositionX: The new X-Position for the M_MonsterTransparency Bitmap. (Tutorial 4, Exercise 1)
		int NewPositionY: The new Y-Position for the M_MonsterTransparency Bitmap. (Tutorial 4, Exercise 1)
	*/
	void Update(int NewPositionX, int NewPositionY);
};

