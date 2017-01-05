#pragma once
#include "GameEntity.h"

// Forward references again (welp):
class GameEntity;

class Enemy : public GameEntity
{
	
private:

	// Properties:

	/** For the route the Enemy is to take for patrolling */
	Vector2D PatrolStartPoint;
	Vector2D PatrolEndPoint;

	// Flags:

	bool MovingToEndPatrolPoint;
	bool PatrollingAnotherCorridor;

	// Functions:

	// For handling sub-patrol movement behavior:

	void MoveRightwardsToPatrolEndPoint();
	void MoveLeftwardsToPatrolEndPoint();
	void MoveRightwardsToPatrolStartPoint();
	void MoveLeftwardsToPatrolStartPoint();

	/** Invert MovingToEndPatrolPoint */
	void MovingToOtherPatrolPoint();

	/**
		For validation.

		@Param: Vector2D TargetPatrolPoint: The point
		this Enemy is moving towards.
	*/
	void ValidateLeftwardsMovement(Vector2D TargetPatrolPoint);
	void ValidateRightwardsMovement(Vector2D TargetPatrolPoint);

	/** Handle moving between points on the patrol */
	void MoveToPatrolEndPoint();
	void MoveToPatrolStartPoint();
	void DeterminePointToMoveTo();

	// Handling general movment
	void MoveLeftwards();
	void MoveRightWards();

public:

	// Functions:

	/** Standard constructor */
	Enemy(SDL_Renderer* RendererToUse, Vector2D NewPatrolEndPoint, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
		Vector2D NewScreenDimensions, EntityID UniqueID, std::string FileName = "Bitmaps/EnemyBitmap.bmp", bool UsesTransparency = true);

	/** Update handler */
	void UpdateEnemy();

	// Flag manipulation:
	void NowPatrollingAnotherCorridor();
	void BackToPatrollingThisCorridor();
};

