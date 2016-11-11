// From bespoke header file(s):
#include "Game.h"

// Perform SDL initialisation:
Game::Game()
{
	// To make sure these pointers are null:
	M_Window = nullptr;
	M_Renderer = nullptr;

	// Initial initialisation:
	SDL_Init(SDL_INIT_VIDEO);

	// Initilise the window:
	M_Window = SDL_CreateWindow(
		"First SDL Window", // Title
		250, // Initial x position
		50, // Initial y position
		640, // Width, in pixels
		480, // Height, in pixels
		0 // Windows behavior flags go here (when required) 
		);

	if (!M_Window)
	{
		printf("Window initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue...\n");
		getchar();
		return;
	}

	// Initilise the renderer:
	M_Renderer = SDL_CreateRenderer(
		M_Window, // The custom window (as delcared in game.h)
		-1, // The specific rendering driver to use (-1 to the first index
		// that supports the specified flags
		0 // Renderer behavior flags
		);

	if (!M_Renderer)
	{
		printf("Renderer initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue...\n");
		getchar();
		return;
	}
}

// Clean up:
Game::~Game()
{
	// Keep in mind that one calls the respective destroy functions
	// in the reverse order of initialisation:

	if (M_Renderer)
	{
		SDL_DestroyRenderer(M_Renderer);
	}

	if (M_Window)
	{
		SDL_DestroyWindow(M_Window);
	}
}

// Clear and present the renderer:
void Game::ClearRenderer()
{
	SDL_RenderClear(M_Renderer);
}

void Game::PresentRenderer()
{
	SDL_RenderPresent(M_Renderer);
}

// Wait for a certain quantity of time:
void Game::Delay(Uint32 Milliseconds)
{
	SDL_Delay(Milliseconds);
}

// Set the display colour as appropriate:
void Game::SetDisplayColour(Uint8 Red, Uint8 Blue, Uint8 Green, Uint8 Alpha)
{
	if (M_Renderer)
	{
		// Set the draw colour to each respective RGBA component (from parameter values):
		int Result = SDL_SetRenderDrawColor(
			M_Renderer,
			Red, // RGB A, for Alpha 
			Green,
			Blue,
			Alpha
			);

		// Clear the window displayed using MRenderer
		// (with its respective draw colour):
		ClearRenderer();

		// Present this to the user:
		PresentRenderer();

		// Allow a 5 second delay for the user to see the result:
		Delay(5000); // As per Sleep(), parse the time in milliseconds
	}
}