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

// Attempt to jump:
void Player::AttemptJump()
{
	// After initiating a jump; this is where the Player will attempt to move to:
	Vector2D ProposedNewHigherPosition = Vector2D(GetEntityPosition().XComponent, 
		GetEntityPosition().YComponent + (CurrentUpwardsMomentum / MOMENTUM_DIVISOR));

	if ((GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions.YComponent).
		AttemptVerticalMovement(ValidMobileEntityMovementValues, ProposedNewHigherPosition)) && (!IsAirborne))
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

// For jumping or falling (if the Player has not jumped):
int Player::GetResultantUpwardsMomentum()
{
	return CurrentUpwardsMomentum /
		MOMENTUM_DIVISOR;
}

// Implement after managing jumping (ideally):
void Player::HandleGravity()
{
	if (HasJumped)
	{ 
		EntityRepresentation->MoveBitmapVertically(GetResultantUpwardsMomentum());
	}
	else
	{
		CurrentUpwardsMomentum = -10;
		EntityRepresentation->MoveBitmapVertically(GetResultantUpwardsMomentum());
	}

	CurrentUpwardsMomentum--;
}