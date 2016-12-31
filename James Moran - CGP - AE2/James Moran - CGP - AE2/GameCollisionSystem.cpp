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
	Vector2D ProposedNewPoint2, EntityDirection MovementDirection)
{
	if (MovementDirection == Leftwards)
	{
		// YComponent for the row number
		int RowNumber = EntityMoving->GetEntityPosition().YComponent / EntityMoving->GetGameLevelBlockDimensions().YComponent;
	
		if (GameEntityIsAtPosition(EntityMoving, RowNumber, ProposedNewPoint1, ProposedNewPoint2))
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

bool GameCollisionSystem::GameEntityIsAtPosition(GameEntity* EntityAttemeptingMovement, int RowToCheck, Vector2D StartingVertex, Vector2D EndingVertex)
{
	// (SIZE IS ABSOLUTE, SUBTRACT NOT FROM IT, OTHERWISE NOT ALL ENTITIES WILL GET CHECKED)
	for (int Iterator = 0; Iterator < GameEntities.at(RowToCheck).size(); Iterator++)
	{
		GameEntity* EntityToCheck = GameEntities.at(RowToCheck).at(Iterator);

		// Only check for position-occupation; if the EntityToCheck is not the EntityAttemptingMovement:
		if (EntityAttemeptingMovement != EntityToCheck)
		{
			if (EntityToCheck->GetIsBlockingEntity() && EntityToCheck->BlockingGameEntityOccupiesPosition(StartingVertex, EndingVertex))
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
	Vector2D EntityWidthHeight = ConsideredEntity->GetEntityExtents();
	Vector2D NewTopLeftCorner = Vector2D(ProposedNewNegativeXPosition, ConsideredEntity->GetEntityPosition().YComponent);
	Vector2D NewBottomLeftCorner = Vector2D(NewTopLeftCorner.XComponent, NewTopLeftCorner.YComponent + EntityWidthHeight.YComponent);
	
	if (!AnotherGameEntityOccupiesRangeBetweenPoints(ConsideredEntity, NewTopLeftCorner, 
		NewBottomLeftCorner, Leftwards))
	{
		// The space is free:
		return true;
	}
	else
	{
		return false;
	}
}

bool GameCollisionSystem::CheckRightSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveXPosition)
{
	return false;
}

bool GameCollisionSystem::CheckTopSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveYPosition)
{
	return false;
}
