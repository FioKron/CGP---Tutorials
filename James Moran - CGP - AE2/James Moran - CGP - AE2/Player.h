#pragma once

#include "GameEntity.h"
#include "GameCollisionSystem.h"


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

	
	int CurrentLives;
	
	// Flags:

	bool HasKey;

	/**
		As the Player is not allowed to jump whilst in the air
		(if they have already jumped, or are falling)
	*/
	bool IsAirborne;

public:
	
	// Functions:

	/** Standard constructor */
	Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
		Vector2D NewScreenDimensions, EntityID UniqueID = EI_PLAYER, 
		std::string FileName = "Bitmaps/HeroBitmap.bmp", bool UsesTransparency = true);

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
};
#endif
