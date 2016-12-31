#pragma once
#include "GameEntity.h"

// Forward references again (welp):
class GameEntity;

class Enemy : public GameEntity
{
	
private:
	/** For the route the Enemy is to take for patrolling */
	Vector2D PatrolStartPoint;
	Vector2D PatrolEndPoint;

public:
	/** Standard constructor */
	Enemy(SDL_Renderer* RendererToUse, Vector2D NewPatrolEndPoint, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
		EntityID UniqueID = EI_ENEMY, std::string FileName = "Bitmaps/EnemyBitmap.bmp", bool UsesTransparency = true);
};

