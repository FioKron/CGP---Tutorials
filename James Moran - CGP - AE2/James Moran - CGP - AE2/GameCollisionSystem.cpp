#include "GameCollisionSystem.h"
//#include "EnemyDoor.h"
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
	// Check all elements in this row:
	for (int Iterator = 0; Iterator < GameEntities.at(RowToCheck).size(); Iterator++)
	{
		GameEntity* EntityToCheck = GameEntities.at(RowToCheck).at(Iterator);

		// Only check for position-occupation; if the EntityToCheck is not the EntityAttemptingMovement:
		if (EntityAttemeptingMovement != EntityToCheck)
		{
			if (EntityToCheck->GetIsBlockingEntity() && 
				EntityToCheck->BlockingGameEntityOccupiesPosition(StartingVertex, EndingVertex, MovementDirection))
			{
				// Make sure the entity is close enough to block the Player:
				switch (MovementDirection)
				{
					// Hence: Only return from this function if this is the case:
				case ED_LEFTWARDS:
					if ((StartingVertex.XComponent <= EntityToCheck->GetEntityTopRightVertex().XComponent) &&
						(StartingVertex.XComponent >= EntityToCheck->GetEntityTopLeftVertex().XComponent))
					{
						EntityIsAtPosition = true;
						return EntityIsAtPosition;
					}
					break;

				case ED_RIGHTWARDS:
					if ((StartingVertex.XComponent >= EntityToCheck->GetEntityTopLeftVertex().XComponent) &&
						(StartingVertex.XComponent <= EntityToCheck->GetEntityTopRightVertex().XComponent))
					{
						EntityIsAtPosition = true;
						return EntityIsAtPosition;
					}
					break;

				case ED_UPWARDS:
					if ((StartingVertex.YComponent >= EntityToCheck->GetEntityBottomLeftVertex().XComponent) &&
						(StartingVertex.YComponent <= EntityToCheck->GetEntityTopLeftVertex().XComponent))
					{
						EntityIsAtPosition = true;
						return EntityIsAtPosition;
					}
					break;

				default:
					break;
				}				
			}
		}
		/**
		if ((StartingVertex.XComponent >= EntityToCheck->GetEntityTopLeftVertex().XComponent) &&
			(StartingVertex.XComponent <= EntityToCheck->GetEntityTopRightVertex().XComponent))
		{
			EntityIsAtPosition = true;
			return EntityIsAtPosition;
		}
		*/
	}

	// No Entity taking up that space if execution reaches this point:
	return EntityIsAtPosition;
}

// For the Entity's row (that is attempting movement):
int GameCollisionSystem::GetEntityRowNumber(GameEntity* EntityMoving)
{
	// YComponent for the row number:
	return EntityMoving->GetEntityPosition().YComponent /
		EntityMoving->GetGameLevelBlockDimensions().YComponent;
}

// ...as well as column:
int GameCollisionSystem::GetEntityColumnNumber(GameEntity * EntityMoving)
{
	// XComponent for the column number:
	return EntityMoving->GetEntityPosition().XComponent / 
		EntityMoving->GetGameLevelBlockDimensions().XComponent;
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

// In effect; a set method: (with minor validation)
void GameCollisionSystem::CopyEnemyDoorEntities(std::vector<GameEntity*> CurrentEnemyDoors)
{
	if (EnemyDoorEntities.empty())
	{
		EnemyDoorEntities = CurrentEnemyDoors;
	}	
}

// Whilst an Enemy is patrolling...
bool GameCollisionSystem::IsEnemyNearAnEnemyDoor(Enemy* ThisEnemyCharacter)
{
	// The return value(s):
	bool EnemyIsNearADoor = false;
	//EnemyDoor* DoorEnemyIsNear;

	for each (GameEntity* CurrentEnemyDoor in EnemyDoorEntities)
	{
		/** 
			Make sure ThisEnemyCharacter is able to access this door
			and the patrol route has not recieved covering:
		
		if ((ThisEnemyCharacter->GetEntityPosition() == CurrentEnemyDoor->GetEntityPosition())
			&& (!CurrentEnemyDoor->GetPatrolRouteCovered()))
		{
			EnemyIsNearADoor = true;
			DoorEnemyIsNear = CurrentEnemyDoor;
			return DoorReferenceAndProximityDetectionFlag(DoorEnemyIsNear, EnemyIsNearADoor);
		}
		*/
	}

	return EnemyIsNearADoor;
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

// IMPLEMENT FULLY:
bool GameCollisionSystem::CheckTopSideCollision(GameEntity* ConsideredEntity)
{
	// For evauluating collision:
	Vector2D ProposedBottomLeftVertex = Vector2D(ConsideredEntity->GetEntityBottomLeftVertex().XComponent +
		ConsideredEntity->GetMovementSpeed() * 10, ConsideredEntity->GetEntityBottomLeftVertex().YComponent);

	Vector2D ProposedBottomRightVertex = Vector2D(ConsideredEntity->GetEntityBottomRightVertex().XComponent +
		ConsideredEntity->GetMovementSpeed() * 10, ConsideredEntity->GetEntityBottomRightVertex().YComponent);

	if (!AnotherGameEntityOccupiesRangeBetweenPoints(ConsideredEntity, ProposedBottomLeftVertex,
		ProposedBottomRightVertex, ED_UPWARDS))
	{
		return true;
	}
	else
	{
		return false;
	}
}
