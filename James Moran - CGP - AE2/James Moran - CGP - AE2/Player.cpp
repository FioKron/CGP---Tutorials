#include "Player.h"

// Initialise this instance:
Player::Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions, 
	Vector2D NewScreenDimensions, EntityID UniqueID, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, NewScreenDimensions, UniqueID, UsesTransparency)
{
	// Player starts with 3 lives, and won't have the key:
	CurrentLives = 3;
	HasKey = false;
	IsAirborne = false;
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

bool Player::GetIsAirborne()
{
	return IsAirborne;
}

void Player::AttemptJump()
{
	if ((GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions.YComponent)
		.CheckTopSideCollision(this)) && (!IsAirborne))
	{
		EntityRepresentation->MoveBitmapUpwards(MOVEMENT_SPEED * 10);
		IsAirborne = true;
	}
}

// Overridden to allow for gravity:
void Player::UpdateEntity()
{
	// Call the super-class's implementation first (for drawing):
	__super::UpdateEntity();

	if (IsAirborne)
	{
		HandleGravity();
	}
}

// Implement after managing jumping (ideally):
void Player::HandleGravity()
{

}