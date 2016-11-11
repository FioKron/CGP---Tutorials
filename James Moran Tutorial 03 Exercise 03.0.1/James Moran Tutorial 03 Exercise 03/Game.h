#pragma once

// For Windows:
#include<stdio.h>

// For SDL:
#include "SDL.h"

/** 
	Foward declared structs, for the Game class to use (a promise to the compiler)
*/
struct SDL_Window;
struct SDL_Renderer;

class Game
{

private:
	/** 
		For SDL to use
	*/
	SDL_Window*		M_Window;
	SDL_Renderer*	M_Renderer;

	/**
		Clear and present the renderer as required:
	*/
	void ClearRenderer();
	void PresentRenderer();

	/**
		Wait for a certain quantity of time

		@Param: Uint32 Milliseconds: The time (in milliseconds) to wait for
	*/
	void Delay(Uint32 Milliseconds);

public:
	/**
		Public functions
	*/
	Game();
	~Game();
	
	/**
		Set the colour of the display

		@Params:

		Uint8 Red: Red colour component.
		Uint8 Green: Green colour component.
		Uint8 Blue: Blue colour component.
		Uint8 Alpha: Alpha component for the transparency level of the RGB components
	*/
	void SetDisplayColour(Uint8 Red, Uint8 Blue, Uint8 Green, Uint8 Alpha);
};

