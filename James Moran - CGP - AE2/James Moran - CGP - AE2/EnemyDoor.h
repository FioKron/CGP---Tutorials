#pragma once
#include "GameEntity.h"
class EnemyDoor : public GameEntity
{
public:
	
	// Functions:

	/** The standard constructor */
	EnemyDoor(SDL_Renderer* RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
		Vector2D NewScreenDimensions, EntityID UniqueID = EI_ENEMY_DOOR, std::string FileName = "Bitmaps/EnemyDoorBitmap.bmp");
	~EnemyDoor();

	// Get methods:

	bool GetPatrolRouteCovered();

	// Flag manipulation:

	/**
	For if this patrol route has received coverage
	by an Enemy (and vice versa for the function below):
	*/
	void PatrolRouteReceivedCoverage();
	void PatrolRouteNotCovered();

	// Operators:
	//void EnemyDoor::operator=(const EnemyDoor& Target);

private:

	// Properties:

	// Flags:
	
	/**
		For if the corridor accessed via this door
		(if this GameEntity is a door),
		has received covering in an Enemy's patrol.
	*/
	bool PatrolRouteCovered;
};

