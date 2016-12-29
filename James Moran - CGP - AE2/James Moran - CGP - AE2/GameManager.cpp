#include "GameManager.h"

// Perform SDL initialisation:
GameManager::GameManager(Vector2D NewGameLevelBlockDimensions, Vector2D NewGameLevelDimensions)
{
	GameWindow = nullptr;
	GameRenderer = nullptr;

	SDL_Init(SDL_INIT_VIDEO);

	// Initilise the window and renderer:
	GameWindow = SDL_CreateWindow(
		"Dungeon Escape", // (Title)
		0, // (Initial x position)
		30, // (Initial y position)
		1000, // (Width, in pixels)
		1000, // (Height, in pixels)
		0 // (Window behavior flags go here (when required)) 
		);

	// Check for validity in both cases:
	if (!GameWindow)
	{
		DisplayConsoleDebugMessage("Window initialisation failed:");
		return;
	}

	GameRenderer = SDL_CreateRenderer(
		GameWindow, // (The custom window (as delcared in game.h))
		-1, // (The specific rendering driver to use (-1 for the first index
		// that supports the specified flags))
		SDL_RENDERER_ACCELERATED // (Renderer behavior flags)
		);

	if (!GameRenderer)
	{
		DisplayConsoleDebugMessage("Renderer initilisation failed:");
		return;
	}

	// For setting up the game level:
	GameLevelBlockDimensions = new Vector2D(NewGameLevelBlockDimensions);
	GameLevelDimensions = new Vector2D(NewGameLevelDimensions);
	GameLevelReference = new GameLevel(GameRenderer, NewGameLevelBlockDimensions, NewGameLevelDimensions);
}

// Clean up:
GameManager::~GameManager()
{
	// (Keep in mind that one calls the respective destroy functions
	// in the reverse order of initialisation):
	if (GameLevelReference)
	{
		delete GameLevelReference;
		GameLevelReference = nullptr;
	}

	if (GameLevelDimensions)
	{
		delete GameLevelDimensions;
		GameLevelDimensions = nullptr;
	}

	if (GameLevelBlockDimensions)
	{
		delete GameLevelBlockDimensions;
		GameLevelBlockDimensions = nullptr;
	}

	if (GameRenderer)
	{
		SDL_DestroyRenderer(GameRenderer);
	}

	if (GameWindow)
	{
		SDL_DestroyWindow(GameWindow);
	}
}

// To display the game level:
void GameManager::InitiateLevelRendering()
{
	GameLevelReference->Render();
	PresentRenderer();
}

// Clear and present the renderer:
void GameManager::ClearRenderer()
{
	SDL_RenderClear(GameRenderer);
}

void GameManager::PresentRenderer()
{
	SDL_RenderPresent(GameRenderer);
}

// Wait for a certain quantity of time:
void GameManager::Delay(Uint32 Milliseconds)
{
	SDL_Delay(Milliseconds);
}

// For debugging:
void GameManager::DisplayConsoleDebugMessage(std::string DebugMessage)
{	
	printf(DebugMessage.c_str());
	printf(" %s\n", SDL_GetError());
	printf("Resuming execution in 5 seconds");
	Delay(5000);
}

// Handle game updates:
void GameManager::Update()
{
	GameLevelReference->UpdateLevelState();
	// (Make sure to present the renderer):
	PresentRenderer();
}

// Get methods:
GameLevel* GameManager::GetGameLevelReference()
{
	return GameLevelReference;	
}
