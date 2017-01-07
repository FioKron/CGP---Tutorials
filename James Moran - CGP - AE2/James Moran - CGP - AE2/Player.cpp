#include "Player.h"

// Initialise this instance:
Player::Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions, 
	Vector2D NewScreenDimensions, std::vector<ValidStartEndPositions> NewValidMobileEntityRowMovementValues,
	std::vector<ValidStartEndPositions> NewValidMobileEntityColumnMovementValues,
	EntityID UniqueID, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, 
		NewScreenDimensions, UniqueID, NewValidMobileEntityRowMovementValues, 
		NewValidMobileEntityColumnMovementValues, UsesTransparency)
{
	// Player starts with 3 lives (test value):
	CurrentLives = 3;
	HasKey = false;
	
	/** VOID:
	//IsAirborne = false;
	//HasJumped = false;

	// For jumping:
	//CurrentUpwardsMomentum = INITIAL_UPWARDS_MOMENTUM;
	*/
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

/**
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
		GetEntityPosition().YComponent - (GetResultantUpwardsMomentum()));

	if (!IsAirborne)
	{
		GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions.YComponent).
			AttemptVerticalMovement(ValidMobileEntityColumnMovementValues, ProposedNewHigherPosition, this);

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
		// For the target position, above the Player:
		Vector2D UpperTargetPosition = Vector2D(GetEntityPosition().XComponent, GetEntityPosition().YComponent +
			GetResultantUpwardsMomentum());

		EntityRepresentation->SetBitmapPosition(GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions
			.XComponent).AttemptVerticalMovement(ValidMobileEntityColumnMovementValues, UpperTargetPosition, this));
	}
	else
	{
		CurrentUpwardsMomentum = -10;

		// For the target position, but this time; as adding a negative value is the same as subtracting
		// the absolute of that value...
		Vector2D LowerTargetPosition = Vector2D(GetEntityPosition().XComponent, GetEntityPosition().YComponent +
			GetResultantUpwardsMomentum());
		
		EntityRepresentation->SetBitmapPosition(GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions
			.XComponent).AttemptVerticalMovement(ValidMobileEntityColumnMovementValues, LowerTargetPosition, this));
	}

	CurrentUpwardsMomentum--;
}
*/