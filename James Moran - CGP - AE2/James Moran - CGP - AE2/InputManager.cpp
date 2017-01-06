#include "InputManager.h"

InputManager::InputManager(Player* NewPlayerReference)
{
	InputEvent = new SDL_Event();
	PlayerReference = NewPlayerReference;

	// Initilise PressedKeys to false (all of it):
	for (int Counter = 0; Counter < KI_PRESSED_KEYS_SIZE; Counter++)
	{
		PressedKeys[Counter] = false;
	}
}

InputManager::~InputManager()
{
	if (InputEvent)
	{
		delete InputEvent;
		InputEvent = nullptr;
	}
}

// For handling the pressing of and releasing of key input:
void InputManager::SetKeyPressed(SDL_Keycode PressedKey)
{
	switch (PressedKey)
	{
	case SDLK_ESCAPE:
		PressedKeys[KI_ESCAPE] = true;
		break;
	case SDLK_w:
		PressedKeys[KI_W] = true;
		PlayerAttemptsJump();
		break;
	case SDLK_a:
		PressedKeys[KI_A] = true;
		PlayerAttemptsLeftwardsMovement();
		break;
	case SDLK_s:
		PressedKeys[KI_S] = true;
		break;
	case SDLK_d:
		PressedKeys[KI_D] = true;
		PlayerAttemptsRightwardsMovement();
		break;
	}
}

void InputManager::SetKeyReleased(SDL_Keycode ReleasedKey)
{
	switch (ReleasedKey)
	{
	case SDLK_ESCAPE:
		PressedKeys[KI_ESCAPE] = false;
		break;
	case SDLK_w:
		PressedKeys[KI_W] = false;
		break;
	case SDLK_a:
		PressedKeys[KI_A] = false;
		break;
	case SDLK_s:
		PressedKeys[KI_S] = false;
		break;
	case SDLK_d:
		PressedKeys[KI_D] = false;
		break;
	}
}

/** 
	Handle the Player attempting movement 
	(leftwards, rightwards and upwards (jumping)):
*/
void InputManager::PlayerAttemptsLeftwardsMovement()
{
	PlayerReference->AttemptHorizontalMovement(ED_LEFTWARDS);
}

void InputManager::PlayerAttemptsRightwardsMovement()
{
	PlayerReference->AttemptHorizontalMovement(ED_RIGHTWARDS);
}

void InputManager::PlayerAttemptsJump()
{
	PlayerReference->AttemptJump();
}

// Poll InputEvent:
void InputManager::Update()
{
	while (SDL_PollEvent(InputEvent) != NULL)
	{
		if (InputEvent->type == SDL_KEYDOWN)
		{
			SDL_Keycode KeyPressed = InputEvent->key.keysym.sym;

			// Determine which key was pressed:
			SetKeyPressed(KeyPressed);			
		}
		else if (InputEvent->type == SDL_KEYUP)
		{
			SDL_Keycode KeyReleased = InputEvent->key.keysym.sym;

			// Determine which key was released:
			SetKeyReleased(KeyReleased);			
		}
	}
}

// Get whether a certain key is pressed:
bool InputManager::KeyIsPressed(KeyIdentity PressedKey)
{
	return PressedKeys[PressedKey];
}