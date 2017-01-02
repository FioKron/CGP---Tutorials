#include "Enemy.h"

Enemy::Enemy(SDL_Renderer * RendererToUse, Vector2D NewPatrolEndPoint, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
	Vector2D NewScreenDimensions, EntityID UniqueID, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, NewScreenDimensions, UniqueID, UsesTransparency)
{
	PatrolStartPoint = Vector2D(XPosition, YPosition);
	PatrolEndPoint = Vector2D(NewPatrolEndPoint);
}

void Enemy::UpdateEnemy()
{
	if (GetEntityPosition().XComponent != PatrolEndPoint.XComponent)
	{
		MoveToPatrolEndPoint();
	}
	else
	{
		MoveToPatrolStartPoint();
	}

	UpdateEntity();
}

// Handle moving between the two points:

void Enemy::MoveToPatrolEndPoint()
{
	if (PatrolEndPoint.XComponent > PatrolStartPoint.XComponent)
	{
		MoveRightwardsToPatrolEndPoint();
	}
	else
	{
		MoveLeftwardsToPatrolEndPoint();
	}

}

void Enemy::MoveToPatrolStartPoint()
{
	if (PatrolStartPoint.XComponent > PatrolEndPoint.XComponent)
	{
		MoveRightwardsToPatrolStartPoint();
	}
	else
	{
		MoveLeftwardsToPatrolStartPoint();
	}
}

void Enemy::MoveRightwardsToPatrolEndPoint()
{
	//AttemptMoveRight();
	EntityRepresentation->MoveBitmapRightwards(MOVEMENT_SPEED);

	if (GetEntityPosition().XComponent > PatrolEndPoint.XComponent)
	{
		EntityRepresentation->SetBitmapPosition(PatrolEndPoint);
	}
}

void Enemy::MoveLeftwardsToPatrolEndPoint()
{
	//AttemptMoveLeft();
	EntityRepresentation->MoveBitmapLeftwards(MOVEMENT_SPEED);

	if (GetEntityPosition().XComponent < PatrolEndPoint.XComponent)
	{
		EntityRepresentation->SetBitmapPosition(PatrolEndPoint);
	}
}

void Enemy::MoveRightwardsToPatrolStartPoint()
{
	//AttemptMoveRight();
	EntityRepresentation->MoveBitmapRightwards(MOVEMENT_SPEED);

	if (GetEntityPosition().XComponent > PatrolStartPoint.XComponent)
	{
		EntityRepresentation->SetBitmapPosition(PatrolStartPoint);
	}
}

void Enemy::MoveLeftwardsToPatrolStartPoint()
{
	//AttemptMoveLeft();
	EntityRepresentation->MoveBitmapLeftwards(MOVEMENT_SPEED);

	if (GetEntityPosition().XComponent < PatrolStartPoint.XComponent)
	{
		EntityRepresentation->SetBitmapPosition(PatrolStartPoint);
	}
}
