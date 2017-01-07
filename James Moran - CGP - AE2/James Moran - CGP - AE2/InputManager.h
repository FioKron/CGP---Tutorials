#pragma once
#include "SDL.h"
#include "Player.h"

// Enum.(s):

enum KeyIdentity
{
	KI_ESCAPE, 
	KI_W, 
	KI_A,
	KI_S,
	KI_D,
	KI_PRESSED_KEYS_SIZE // For the number of keys that the Player can press:
};

class InputManager
{
public:

	// Functions:
	
	void Update();
	bool KeyIsPressed(KeyIdentity PressedKey);

	/**
		Standard constructor.

		@Param: Player* NewPlayerReference: To update the Player's
		current position, for when they provide movement input.
	*/
	InputManager(Player* NewPlayerReference);
	
	/** Standard destructor */
	~InputManager();

private:
	
	// Properties:

	/** For all input */
	SDL_Event* InputEvent;

	/** To refer to the Player (for attempting movement) */
	Player* PlayerReference;

	/** For the current pressed or released state of input keys */
	bool PressedKeys[KI_PRESSED_KEYS_SIZE];

	// Functions:

	/** 
		Description: Set PressedKey as the key that was pressed,
		in PressedKeys[].

		@Param: SDL_Keycode PressedKey: The keycode for the key 
		that was pressed.
	*/
	void SetKeyPressed(SDL_Keycode PressedKey);

	/** 
		Description: Set ReleasedKey as the key that was released,
		in PressedKeys[].

		@Param: SDL_Keycode ReleasedKey: The keycode for the key 
		that was released.
	*/
	void SetKeyReleased(SDL_Keycode ReleasedKey);

	// Handle Player movement:
	void PlayerAttemptsLeftwardsMovement();
	void PlayerAttemptsRightwardsMovement();
	void PlayerAttemptsUpwardsMovement();
	void PlayerAttemptsDownwardsMovement();
};

