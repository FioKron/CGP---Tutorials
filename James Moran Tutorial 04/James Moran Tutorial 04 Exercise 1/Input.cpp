#include "Input.h"



Input::Input()
{
	// Initilise bKeysPressed to false (all of it):
	for (int Counter = 0; Counter < PRESSED_KEYS_SIZE; Counter++)
	{
		bKeysPressed[Counter] = false;
	}
}


Input::~Input()
{

}

void Input::Update()
{
	while (SDL_PollEvent(&M_Event) != NULL)
	{
		if (M_Event.type == SDL_KEYDOWN)
		{
			SDL_Keycode KeyPressed = M_Event.key.keysym.sym;

			// Determine which key was pressed:
			switch (KeyPressed)
			{
			case SDLK_ESCAPE:
				bKeysPressed[KEY_ESCAPE] = true;
				break;
			case SDLK_r:
				bKeysPressed[KEY_R] = true;
				break;
			case SDLK_g:
				bKeysPressed[KEY_G] = true;
				break;
			case SDLK_b:
				bKeysPressed[KEY_B] = true;
				break;
			case SDLK_t:
				bKeysPressed[KEY_R] = true;
				break;
			case SDLK_h:
				bKeysPressed[KEY_H] = true;
				break;
			case SDLK_n:
				bKeysPressed[KEY_N] = true;
				break;
			}
		}
		else if (M_Event.type == SDL_KEYUP)
		{
			SDL_Keycode KeyPressed = M_Event.key.keysym.sym;

			// Determine which key was released:
			switch (KeyPressed)
			{
			case SDLK_ESCAPE:
				bKeysPressed[KEY_ESCAPE] = false;
				break;
			case SDLK_r:
				bKeysPressed[KEY_R] = false;
				break;
			case SDLK_g:
				bKeysPressed[KEY_G] = false;
				break;
			case SDLK_b:
				bKeysPressed[KEY_B] = false;
				break;
			case SDLK_t:
				bKeysPressed[KEY_R] = false;
				break;
			case SDLK_h:
				bKeysPressed[KEY_H] = false;
				break;
			case SDLK_n:
				bKeysPressed[KEY_N] = false;
				break;
			}
		}
	}
}

// Get whether a certain key is pressed:
bool Input::KeyIsPressed(PressedKeys PressedKey)
{
	return bKeysPressed[PressedKey];
}