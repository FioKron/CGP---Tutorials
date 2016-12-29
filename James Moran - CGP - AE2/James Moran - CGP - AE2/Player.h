#pragma once

#include "GameEntity.h"
#include "GameCollisionSystem.h"

/**
	The class for the Player, the goal of them game for them;
	is to get the key and escape from this dungeon level.
*/
class Player : public GameEntity
{

private:

	// Properties:

	bool HasKey;
	int CurrentLives;

public:
	
	// Functions:

	/** Standard constructor */
	Player(SDL_Renderer* RendererToUse, int XPosition, int YPosition,
		EntityID UniqueID = PlayerID, std::string FileName = "Bitmaps/HeroBitmap.bmp", bool UsesTransparency = true);
	
	// Movement handling:
	void AttemptMoveLeft();
	void AttemptMoveRight();
	void AttemptJump();

	// Get methods:

	bool GetHasKey();
	int GetCurrentLives();
};

