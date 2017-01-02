#include "GameCollisionSystem.h"
#include <iostream> // For debugging

// For initialisation:
GameCollisionSystem::GameCollisionSystem()
{

}

// For cleaning up:
GameCollisionSystem::~GameCollisionSystem()
{

}

bool GameCollisionSystem::AnotherGameEntityOccupiesRangeBetweenPoints(GameEntity* EntityMoving, Vector2D ProposedNewPoint1, 
	Vector2D ProposedNewPoint2, EntityMovementDirection MovementDirection)
{
	if (MovementDirection == ED_LEFTWARDS)
	{
		// YComponent for the row number
		int RowNumber = EntityMoving->GetEntityPosition().YComponent / EntityMoving->GetGameLevelBlockDimensions().YComponent;
	
		if (GameEntityIsAtPosition(EntityMoving, RowNumber, ProposedNewPoint1, ProposedNewPoint2, MovementDirection))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// No entities occupy the space:
	return false;
}

bool GameCollisionSystem::GameEntityIsAtPosition(GameEntity* EntityAttemeptingMovement, int RowToCheck, Vector2D StartingVertex, 
	Vector2D EndingVertex, EntityMovementDirection MovementDirection)
{
	// (SIZE IS ABSOLUTE, SUBTRACT NOT FROM IT, OTHERWISE NOT ALL ENTITIES WILL GET CHECKED)
	for (int Iterator = 0; Iterator < GameEntities.at(RowToCheck).size(); Iterator++)
	{
		GameEntity* EntityToCheck = GameEntities.at(RowToCheck).at(Iterator);

		// Only check for position-occupation; if the EntityToCheck is not the EntityAttemptingMovement:
		if (EntityAttemeptingMovement != EntityToCheck)
		{
			if (EntityToCheck->GetIsBlockingEntity() && 
				EntityToCheck->BlockingGameEntityOccupiesPosition(StartingVertex, EndingVertex, MovementDirection))
			{
				if (EntityToCheck->GetUniqueID() == EI_WALL_BLOCK)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}

	// No Entity taking up that space if execution reaches this point:
	return false;
}

// For adding Entities to this collection, for future collision reference checking:
// RESOLVE ISSUES HERE!?F!£F!£
void GameCollisionSystem::AddGameEntityToCollection(GameEntity* EntityToAdd)
{
	if (EntityToAdd)
	{
		if (TemporaryRow.size() < GameEntitiesPerRow)
		{
			TemporaryRow.push_back(EntityToAdd);
		}
		else
		{
			GameEntities.push_back(TemporaryRow);
			TemporaryRow.clear();
			TemporaryRow.push_back(EntityToAdd);
		}	
	}	
}

/** 
	Check for collision on the left, right and top 
	sides respectivley.
*/
bool GameCollisionSystem::CheckLeftSideCollision(GameEntity* ConsideredEntity, int ProposedNewNegativeXPosition)
{
	// For evauluating collision:
	Vector2D NewTopLeftVertex = ConsideredEntity->GetEntityTopLeftVertex();
	NewTopLeftVertex.XComponent = ProposedNewNegativeXPosition;
	Vector2D NewBottomLeftVertex = ConsideredEntity->GetEntityBottomLeftVertex();
	NewBottomLeftVertex.XComponent = ProposedNewNegativeXPosition;

	if (!AnotherGameEntityOccupiesRangeBetweenPoints(ConsideredEntity, NewTopLeftVertex,
		NewBottomLeftVertex, ED_LEFTWARDS))
	{
		// The space is free:
		return true;
	}
	else
	{
		return false;
	}
}

// RESOLVE CHECKING RIGHT:
bool GameCollisionSystem::CheckRightSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveXPosition)
{
	// For evauluating collision:
	Vector2D NewTopRightVertex = ConsideredEntity->GetEntityTopRightVertex();
	NewTopRightVertex.XComponent = ProposedNewPositiveXPosition;
	Vector2D NewBottomRightVertex = ConsideredEntity->GetEntityBottomRightVertex();
	NewBottomRightVertex.XComponent = ProposedNewPositiveXPosition;

	if (!AnotherGameEntityOccupiesRangeBetweenPoints(ConsideredEntity, NewTopRightVertex,
		NewBottomRightVertex, ED_RIGHTWARDS))
	{
		// This space is free:
		return true;
	}
	else
	{
		return false;
	}
}
bool GameCollisionSystem::CheckTopSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveYPosition)
{
	return false;
}
