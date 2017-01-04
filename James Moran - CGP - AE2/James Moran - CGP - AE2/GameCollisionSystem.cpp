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

// If another blocking game Entity occupies this position:
bool GameCollisionSystem::AnotherGameEntityOccupiesRangeBetweenPoints(GameEntity* EntityMoving, Vector2D ProposedNewPoint1, 
	Vector2D ProposedNewPoint2, EntityMovementDirection MovementDirection)
{
	if (GameEntityIsAtPosition(EntityMoving, GetEntityRowNumber(EntityMoving), ProposedNewPoint1, ProposedNewPoint2, MovementDirection))
	{
		return true;
	}
	else
	{
		return false;
	}
	
	// No entities occupy the space:
	return false;
}

bool GameCollisionSystem::GameEntityIsAtPosition(GameEntity* EntityAttemeptingMovement, int RowToCheck, Vector2D StartingVertex, 
	Vector2D EndingVertex, EntityMovementDirection MovementDirection)
{
	// The flag to return: 
	bool EntityIsAtPosition = false;

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
				EntityIsAtPosition = true;
				return EntityIsAtPosition;
			}
			/**
			else
			{
				return false;
			}
			*/
		}

		if (Iterator == GameEntities.at(RowToCheck).size() - 1)
		{
			return EntityIsAtPosition;
		}

	}

	// No Entity taking up that space if execution reaches this point:
	return EntityIsAtPosition;
}

// For the Entity's row (that is attempting movement):
int GameCollisionSystem::GetEntityRowNumber(GameEntity* EntityMoving)
{
	// YComponent for the row number
	return EntityMoving->GetEntityPosition().YComponent / EntityMoving->GetGameLevelBlockDimensions().YComponent;
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
bool GameCollisionSystem::CheckLeftSideCollision(GameEntity* ConsideredEntity)
{
	// For evauluating collision:
	Vector2D ProposedTopLeftVertex = Vector2D(ConsideredEntity->GetEntityTopLeftVertex().XComponent -
		ConsideredEntity->GetMovementSpeed(), ConsideredEntity->GetEntityTopLeftVertex().YComponent);
	
	Vector2D ProposedBottomLeftVertex = Vector2D(ConsideredEntity->GetEntityBottomLeftVertex().XComponent -
		ConsideredEntity->GetMovementSpeed(), ConsideredEntity->GetEntityBottomLeftVertex().YComponent);

	if (!AnotherGameEntityOccupiesRangeBetweenPoints(ConsideredEntity, ProposedTopLeftVertex,
		ProposedBottomLeftVertex, ED_LEFTWARDS))
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
bool GameCollisionSystem::CheckRightSideCollision(GameEntity* ConsideredEntity)
{
	// For evauluating collision:
	Vector2D ProposedTopRightVertex = Vector2D(ConsideredEntity->GetEntityTopRightVertex().XComponent +
		ConsideredEntity->GetMovementSpeed(), ConsideredEntity->GetEntityTopRightVertex().YComponent);

	Vector2D ProposedBottomRightVertex = Vector2D(ConsideredEntity->GetEntityBottomRightVertex().XComponent +
		ConsideredEntity->GetMovementSpeed(), ConsideredEntity->GetEntityBottomRightVertex().YComponent);

	if (!AnotherGameEntityOccupiesRangeBetweenPoints(ConsideredEntity, ProposedTopRightVertex,
		ProposedBottomRightVertex, ED_RIGHTWARDS))
	{
		// This space is free:
		return true;
	}
	else
	{
		return false;
	}
}
bool GameCollisionSystem::CheckTopSideCollision(GameEntity* ConsideredEntity)
{
	return false;
}
