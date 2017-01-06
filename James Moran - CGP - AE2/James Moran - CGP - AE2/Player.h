#pragma once

#include "GameEntity.h"
#include "GameCollisionSystem.h"
#include <vector>


#ifndef PLAYER_H
#define PLAYER_H
/**
	The class for the Player, the goal of them game for them;
	is to get the key and escape from this dungeon level.
*/
class Player : public GameEntity
{

private:

	// Properties:

	/** Whilst propelling themselves upwards (e.g. via jumping) */
	int CurrentUpwardsMomentum;
	
	int CurrentLives;

	// Constant values:
	
	/**
		These values are for handling jumping:
	*/
	const int INITIAL_UPWARDS_MOMENTUM = 30;

	/** 
		Given int division, as the resultant value is floored;
		CurrentUpwardsMomentum will change at every multiple of 10 - 1
		(e.g. 29, 19 etc.)
	*/
	const float MOMENTUM_DIVISOR = 1;

	// Flags:

	bool HasKey;

	/**
		As the Player is not allowed to jump whilst in the air
		(if they have already jumped, or are falling)
	*/
	bool IsAirborne;

	/** If the Player causes themselves to become airborne */
	bool HasJumped;

public:
	
	// Functions:

	/** Standard constructor */
	Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
		Vector2D NewScreenDimensions, std::vector<ValidStartEndXPositionsPerRow> NewValidMobileEntityMovementValues,
		EntityID UniqueID = EI_PLAYER, std::string FileName = "Bitmaps/HeroBitmap.bmp", bool UsesTransparency = true);

	/** Only the Player can jump (Enemies follow a preset patrol route) */
	void AttemptJump();

	/** For handling falling (such as after jumping) */
	void HandleGravity();

	/** For a gravity sub-system */
	void UpdateEntity()override;

	// Get methods:

	bool GetHasKey();
	int GetCurrentLives();
	bool GetIsAirborne();
	bool GetHasJumped();
};
#endif
