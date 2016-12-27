#include "InputManager.h"

InputManager::InputManager(Player* NewPlayerReference)
{
	InputEvent = new SDL_Event();
	PlayerReference = NewPlayerReference;

	// Initilise PressedKeys to false (all of it):
	for (int Counter = 0; Counter < PRESSED_KEYS_SIZE; Counter++)
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
		PressedKeys[KEY_ESCAPE] = true;
		break;
	case SDLK_w:
		PressedKeys[KEY_W] = true;
		PlayerAttemptsJump();
		break;
	case SDLK_a:
		PressedKeys[KEY_A] = true;
		PlayerAttemptsLeftwardsMovement();
		break;
	case SDLK_s:
		PressedKeys[KEY_S] = true;
		break;
	case SDLK_d:
		PressedKeys[KEY_D] = true;
		PlayerAttemptsRightwardsMovement();
		break;
	}
}

void InputManager::SetKeyReleased(SDL_Keycode ReleasedKey)
{
	switch (ReleasedKey)
	{
	case SDLK_ESCAPE:
		PressedKeys[KEY_ESCAPE] = false;
		break;
	case SDLK_w:
		PressedKeys[KEY_W] = false;
		break;
	case SDLK_a:
		PressedKeys[KEY_A] = false;
		break;
	case SDLK_s:
		PressedKeys[KEY_S] = false;
		break;
	case SDLK_d:
		PressedKeys[KEY_D] = false;
		break;
	}
}

/** 
	Handle the Player attempting movement 
	(leftwards, rightwards and upwards (jumping)):
*/
void InputManager::PlayerAttemptsLeftwardsMovement()
{
	// Test:
	PlayerReference->AttemptMoveLeft();
}

void InputManager::PlayerAttemptsRightwardsMovement()
{
	// Test:
	PlayerReference->AttemptMoveRight();
}

void InputManager::PlayerAttemptsJump()
{
	// Test:
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