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

	// For handling sub-patrol-movement behavior:

	void MoveRightwardsToPatrolEndPoint();
	void MoveLeftwardsToPatrolEndPoint();
	void MoveRightwardsToPatrolStartPoint();
	void MoveLeftwardsToPatrolStartPoint();

public:
	/** Standard constructor */
	Enemy(SDL_Renderer* RendererToUse, Vector2D NewPatrolEndPoint, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
		Vector2D NewScreenDimensions, EntityID UniqueID = EI_ENEMY, std::string FileName = "Bitmaps/EnemyBitmap.bmp", bool UsesTransparency = true);

	/** Update handler */
	void UpdateEnemy();

	/** Handle moving between points on the patrol */
	void MoveToPatrolEndPoint();
	void MoveToPatrolStartPoint();
};

