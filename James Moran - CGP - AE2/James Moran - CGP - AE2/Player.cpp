#include "Player.h"

// Initialise this instance:
Player::Player(SDL_Renderer * RendererToUse, int XPosition, int YPosition, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, UsesTransparency)
{
	// Player starts with 3 lives, and won't have the key:
	CurrentLives = 3;
	HasKey = false;
}

// Handle attempts at movement:
void Player::AttemptMoveLeft()
{
	/** For now; simply move the Player left and right */
	//CleanUpPreviousPosition();
	EntityScreenPosition.XComponent--;
}

void Player::AttemptMoveRight()
{
	//CleanUpPreviousPosition();
	EntityScreenPosition.XComponent++;
}

void Player::AttemptJump()
{

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
