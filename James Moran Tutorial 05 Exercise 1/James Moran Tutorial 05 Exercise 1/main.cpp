#include "Game.h"
#include "Input.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// For handling game and input logic:
	Game* GameReference = new Game();
	Input* InputReference = new Input();

	// For Tutorial 4, Exercise 1: To move the bitmap with a transparency key:
	//int CurrentMonsterPositionX = 0;
	//int CurrentMonsterPositionY = 0; 

	// Only use this pointer if the respective object is valid:
	if (GameReference && InputReference)
	{
		// Constant colour values (hmm):
		Uint8 R = 127;
		Uint8 G = 127;
		Uint8 B = 127;
		Uint8 A = 255;

		while (!InputReference->KeyIsPressed(KEY_ESCAPE))
		{
			InputReference->Update();

			GameReference->SetDisplayColour(R, G, B, A);
			GameReference->Update();
		}

		delete InputReference;
		InputReference = nullptr;

		// Clean up pointers:
		delete GameReference;
		GameReference = nullptr;	
	}

	// (A) Standard return value:
	return 0;
}