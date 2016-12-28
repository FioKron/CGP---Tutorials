#pragma once

/**
	This class handles what is present in the one and only (as it stands), level.
	Holding a reference to the current game level; which then handles the Entities 
	present within it.
*/

// For what is not included in SDL:
#include <stdio.h>

// Bespoke classes (which include SDL):
#include "GameLevel.h"

class GameManager
{

private:

	// Properties:

	/** 
		For SDL to use
	*/
	SDL_Window* GameWindow;
	SDL_Renderer* GameRenderer;

	/** For refering to the level */
	GameLevel* GameLevelReference;
	Vector2D* GameLevelBlockDimensions;
	Vector2D* GameLevelDimensions;

	// Functions:

	/**
		Clear and present the renderer as required:
	*/
	void ClearRenderer();
	void PresentRenderer();

	/**
		Wait for a certain quantity of time.

		@Param: Uint32 Milliseconds: The time (in milliseconds) to wait for
	*/
	void Delay(Uint32 Milliseconds);

	/**
		Print DebugMessage to the console.

		@Param: std::string DebugMessage: The message to show
	*/
	void DisplayConsoleDebugMessage(std::string DebugMessage);

public:
	
	// Functions:
	
	/**
		Standard Constructor.

		@Params: Vector2D NewGameLevelBlockDimensions: The dimensions of 
		each block, for the GameLevel to use in construction of the level
		(in pixels).

		Vector2D NewGameLevelDimensions: The dimensions of the game level for
		GameLevel to handle the construction of (in level blocks).
	*/
	GameManager(Vector2D NewGameLevelBlockDimensions, Vector2D NewGameLevelDimensions);
	
	/** Standard Destructor */
	~GameManager();

	/** For initiating level rendering */
	void InitiateLevelRendering();

	/**
		For updating game components
	*/
	void Update();

	// Get methods:

	/** For getting components of the game-level */
	GameLevel* GetGameLevelReference();
};

