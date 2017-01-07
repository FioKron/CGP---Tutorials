#include "Enemy.h"
#include "Windows.h"

#include <iostream> // For debugging

// Initialisation:
Enemy::Enemy(SDL_Renderer* RendererToUse, Vector2D NewPatrolEndPoint, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
	Vector2D NewScreenDimensions, EntityID UniqueID, std::vector<ValidStartEndPositions> NewValidMobileEntityRowMovementValues,
	std::vector<ValidStartEndPositions> NewValidMobileEntityColumnMovementValues, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, NewScreenDimensions,
		UniqueID, NewValidMobileEntityRowMovementValues, NewValidMobileEntityColumnMovementValues, UsesTransparency)
{
	PatrolStartPoint = Vector2D(XPosition, YPosition);
	PatrolEndPoint = Vector2D(NewPatrolEndPoint);

	MovingToEndPatrolPoint = true;
	PatrollingAnotherCorridor = false;

	TestTimer = 0.0f;
}

// For updating this Enemy:
void Enemy::UpdateEnemy()
{
	// Only whilst they have a presence on the game level:
	if (!PatrollingAnotherCorridor)
	{	
		if (GameCollisionSystem::GetCollisionSystem(20).IsEnemyNearAnEnemyDoor(this))
		{
			NowPatrollingAnotherCorridor();
			return;
		}
		
		DeterminePointToMoveTo();
		UpdateEntity();
	}
	else
	{
		EntityRepresentation->SetBitmapPosition(Vector2D(-50, -50));

		TestTimer++;

		if (TestTimer == 3000.0f)
		{
			BackToPatrollingThisCorridor();
		}
	}
}

// Flag manipulation:
void Enemy::NowPatrollingAnotherCorridor()
{
	PatrollingAnotherCorridor = true;
}

void Enemy::BackToPatrollingThisCorridor()
{
	PatrollingAnotherCorridor = false;
}

// Handle moving between the two points:

void Enemy::DeterminePointToMoveTo()
{
	if (MovingToEndPatrolPoint)
	{
		MoveToPatrolEndPoint();
	}
	else
	{
		MoveToPatrolStartPoint();
	}
}

void Enemy::MoveToPatrolEndPoint()
{
	if (UniqueID == EI_LOWEST_ENEMY)
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
	if (UniqueID == EI_HIGHEST_ENEMY)
	{
		MoveRightwardsToPatrolStartPoint();
	}
	else
	{
		MoveLeftwardsToPatrolStartPoint();
	}
}

// Move in the appropriate movement direction: 

void Enemy::MoveRightwardsToPatrolEndPoint()
{
	//AttemptMoveRight();
	MoveRightWards();
	ValidateRightwardsMovement(PatrolEndPoint);
}

void Enemy::MoveLeftwardsToPatrolEndPoint()
{
	//AttemptMoveLeft();
	MoveLeftwards();
	ValidateLeftwardsMovement(PatrolEndPoint);
}

void Enemy::MoveRightwardsToPatrolStartPoint()
{
	//AttemptMoveRight();
	MoveRightWards();
	ValidateRightwardsMovement(PatrolStartPoint);
}

void Enemy::MoveLeftwardsToPatrolStartPoint()
{
	//AttemptMoveLeft();
	MoveLeftwards();
	ValidateLeftwardsMovement(PatrolStartPoint);
}

// Attempt to move leftwards...
void Enemy::MoveLeftwards()
{
	AttemptHorizontalMovement(ED_LEFTWARDS);
	if ((GetEntityPosition() == PatrolStartPoint) ||
		(GetEntityPosition() == PatrolEndPoint))
	{
		// Signal that it is time to move to the other
		// patrol point then:
		MovingToOtherPatrolPoint();
	}
	else
	{
		WaitAfterTranslation(WAIT_TIME_BETWEEN_MOVEMENT_ATTEMPTS);
	}	
}

// ...or rightwards:
void Enemy::MoveRightWards()
{
	AttemptHorizontalMovement(ED_RIGHTWARDS);

	if ((GetEntityPosition() == PatrolStartPoint) ||
		(GetEntityPosition() == PatrolEndPoint))
	{
		// Signal that it is time to move to the other
		// patrol point then:
		MovingToOtherPatrolPoint();
	}
	else
	{
		WaitAfterTranslation(WAIT_TIME_BETWEEN_MOVEMENT_ATTEMPTS);
	}
}

// To allow the Player to avoid collision with this Enemy:
void Enemy::WaitAfterTranslation(Uint32 MilliSeconds)
{
	SDL_Delay(MilliSeconds);
}

// Invert this flag:
void Enemy::MovingToOtherPatrolPoint()
{
	MovingToEndPatrolPoint = !MovingToEndPatrolPoint;
}

// Handle movement validation:

void Enemy::ValidateLeftwardsMovement(Vector2D TargetPatrolPoint)
{
	if (GetEntityPosition().XComponent <= TargetPatrolPoint.XComponent)
	{
		MovingToOtherPatrolPoint();
	}
}

void Enemy::ValidateRightwardsMovement(Vector2D TargetPatrolPoint)
{
	if (GetEntityPosition().XComponent >= TargetPatrolPoint.XComponent)
	{
		MovingToOtherPatrolPoint();
	}
}