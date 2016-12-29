#include "Player.h"

// Initialise this instance:
Player::Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, EntityID UniqueID, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, UniqueID, UsesTransparency)
{
	// Player starts with 3 lives, and won't have the key:
	CurrentLives = 3;
	HasKey = false;
}

// Handle attempts at movement:
void Player::AttemptMoveLeft()
{
	if (GameCollisionSystem::GetCollisionSystem().CheckLeftSideCollision(this, EntityRepresentation->GetBitmapPosition().XComponent - 1))
	{
		// Declare a movement speed later:
		EntityRepresentation->MoveBitmapLeftwards(1);
	}
}

void Player::AttemptMoveRight()
{

	//EntityScreenPosition.XComponent++;
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
