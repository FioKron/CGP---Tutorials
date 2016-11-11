#include "Game.h"

int main(int argc, char* argv[])
{
	Game* GameReference = new Game();

	// Only use this pointer if the respective object is valid:
	if (GameReference)
	{
		GameReference->SetDisplayColour();

		// Proper cleanup for a pointer:
		delete GameReference;
		GameReference = nullptr;
	}

	// (A) Standard return value:
	return 0;
}