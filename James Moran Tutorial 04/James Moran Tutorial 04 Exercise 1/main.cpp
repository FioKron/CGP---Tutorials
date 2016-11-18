#include "Game.h"
#include "Input.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Game* GameReference = new Game();
	Input* InputReference = new Input();

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


			// Increase the values of red, green, and blue by 1, respectivly (from 0 to 255):
			if (InputReference->KeyIsPressed(KEY_R))
			{
				// For each value, check if R + 1 is greater than 255:
				if (++R > 255)
				{
					R = 255;
				}
				
				std::cout << (int)R << std::endl;
			}

			if (InputReference->KeyIsPressed(KEY_G))
			{
				if (++G > 255)
				{
					G = 255;
				}
			}

			if (InputReference->KeyIsPressed(KEY_B))
			{
				if (++B > 255)
				{
					B = 255;
				}
			}

			// Reduce the RGB values by 1, respectivly:
			if (InputReference->KeyIsPressed(KEY_T))
			{
				if (--R < 0)
				{
					R = 0;
				}
			}

			if (InputReference->KeyIsPressed(KEY_H))
			{
				if (--G < 0)
				{
					G = 0;
				}
			}

			if (InputReference->KeyIsPressed(KEY_N))
			{
				if (--B < 0)
				{
					B = 0;
				}
			}

			GameReference->SetDisplayColour(R, G, B, A);
			GameReference->Update();
		}

		// Clean up pointers:
		delete GameReference;
		GameReference = nullptr;

		delete GameReference;
		GameReference = nullptr;
	}

	// (A) Standard return value:
	return 0;
}