#include "Player.h"

// Initialise this instance:
Player::Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions, EntityID UniqueID, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, UniqueID, UsesTransparency)
{
	// Player starts with 3 lives, and won't have the key:
	CurrentLives = 3;
	HasKey = false;
}

// Handle attempts at movement:
void Player::AttemptMoveLeft()
{
	// Testing:
	int MovementSpeed = 2;

	if (GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions.YComponent).CheckLeftSideCollision(this, EntityRepresentation->GetBitmapPosition().XComponent - MovementSpeed))
	{
		// Declare a movement speed later:
		EntityRepresentation->MoveBitmapLeftwards(MovementSpeed);
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
