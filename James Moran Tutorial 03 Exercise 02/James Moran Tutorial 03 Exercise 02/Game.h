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

public:
	/**
		Public functions
	*/
	Game();
	~Game();
	void SetDisplayColour(void);
};

