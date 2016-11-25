#pragma once
#include "SDL.h"

// Enum.(s):

enum PressedKeys
{
	KEY_ESCAPE, 
	KEY_R, 
	KEY_G,
	KEY_B,
	KEY_T,
	KEY_H,
	KEY_N,
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	PRESSED_KEYS_SIZE // Interesting...
};

class Input
{
public:
	void Update();
	bool KeyIsPressed(PressedKeys PressedKey);

	Input();
	~Input();

private:
	SDL_Event M_Event;
	bool bKeysPressed[PRESSED_KEYS_SIZE];
};

