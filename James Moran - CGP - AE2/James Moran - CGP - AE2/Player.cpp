#include "Player.h"

// Initialise this instance:
Player::Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions, 
	Vector2D NewScreenDimensions, EntityID UniqueID, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, NewScreenDimensions, UniqueID, UsesTransparency)
{
	// Player starts with 3 lives, and won't have the key:
	CurrentLives = 3;
	HasKey = false;
}

/**
	Get methods:
*/
bool Player::GetHasKey()
{
	return HasKey;
}

int Player::GetCurrentLives()
{
	return CurrentLives;
}
