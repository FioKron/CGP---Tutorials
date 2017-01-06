#include "Player.h"

// Initialise this instance:
Player::Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions, 
	Vector2D NewScreenDimensions, std::vector<ValidStartEndXPositionsPerRow> NewValidMobileEntityMovementValues,
	EntityID UniqueID, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, 
		NewScreenDimensions, UniqueID, NewValidMobileEntityMovementValues, UsesTransparency)
{
	// Player starts with 3 lives (test value):
	CurrentLives = 3;
	HasKey = false;
	IsAirborne = false;
	HasJumped = false;

	// For jumping:
	CurrentUpwardsMomentum = INITIAL_UPWARDS_MOMENTUM;
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

bool Player::GetHasJumped()
{
	return HasJumped;
}

void Player::AttemptJump()
{
	if ((GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions.YComponent)
		.CheckTopSideCollision(this)) && (!IsAirborne))
	{
		// The HandleGravity method will handle Player movement now:
		HasJumped = true;
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
	int ResultantUpwardsMomentum = CurrentUpwardsMomentum /
		MOMENTUM_DIVISOR;

	if (HasJumped)
	{
		EntityRepresentation->MoveBitmapUpwards(ResultantUpwardsMomentum);
	}
	else
	{
		ResultantUpwardsMomentum = -10;
		EntityRepresentation->MoveBitmapUpwards(ResultantUpwardsMomentum);
	}

	CurrentUpwardsMomentum--;
}