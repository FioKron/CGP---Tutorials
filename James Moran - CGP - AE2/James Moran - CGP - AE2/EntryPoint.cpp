#include "GameManager.h"
#include "InputManager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// (Declare and use constant values for these two properties):
	Vector2D BlockDimensions = Vector2D(50, 50); // Pixels here
	Vector2D LevelDimensions = Vector2D(20, 20); // Blocks here

	GameManager* GameReference = new GameManager(BlockDimensions, LevelDimensions);
	InputManager* InputReference = new InputManager(GameReference->GetGameLevelReference()->GetPlayerCharacterReference());
	
	// For validity, once again:
	if (GameReference && InputReference)
	{
		// Initilise initilisation of the game's level:
		GameReference->InitiateLevelRendering();

		while (!InputReference->KeyIsPressed(KEY_ESCAPE))
		{
			InputReference->Update();
			GameReference->Update();
		}

		// Clean up pointers:
		delete GameReference;
		GameReference = nullptr;

		delete InputReference;
		InputReference = nullptr;
	}

	// (A) Standard return value:
	return 0;
}