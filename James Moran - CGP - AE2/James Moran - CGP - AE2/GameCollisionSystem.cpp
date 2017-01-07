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
	if (GameEntityIsAtRowPosition(EntityMoving, GetEntityRowNumber(EntityMoving), ProposedNewPoint1, ProposedNewPoint2, MovementDirection))
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

bool GameCollisionSystem::GameEntityIsAtRowPosition(GameEntity* EntityAttemeptingMovement, int RowToCheck, Vector2D StartingVertex, 
	Vector2D EndingVertex, EntityMovementDirection MovementDirection)
{
	// The flag to return: 
	bool EntityIsAtPosition = false;

	// (SIZE IS ABSOLUTE, SUBTRACT NOT FROM IT, OTHERWISE NOT ALL ENTITIES WILL GET CHECKED)
	// Check all elements in this row:
	for (int Iterator = 0; Iterator < GameEntities[RowToCheck].size(); Iterator++)
	{
		GameEntity* EntityToCheck = GameEntities[RowToCheck][Iterator];

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
					if ((StartingVertex.YComponent >= EntityToCheck->GetEntityBottomLeftVertex().YComponent) &&
						(StartingVertex.YComponent <= EntityToCheck->GetEntityTopLeftVertex().YComponent))
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

bool GameCollisionSystem::GameEntityIsAtColumnPosition(GameEntity* EntityAttemeptingMovement, int ColumnToCheck, Vector2D TopLeftVertex,
	Vector2D TopRightVertex, EntityMovementDirection MovementDirection)
{
	// The flag to return: 
	bool EntityIsAtPosition = false;

	// (SIZE IS ABSOLUTE, SUBTRACT NOT FROM IT, OTHERWISE NOT ALL ENTITIES WILL GET CHECKED)
	// Check all elements in this row:
	for (int Iterator = 0; Iterator < GameEntities[Iterator].size(); Iterator++)
	{
		GameEntity* EntityToCheck = GameEntities[Iterator][ColumnToCheck];

		// Only check for position-occupation; if the EntityToCheck is not the EntityAttemptingMovement:
		if (EntityAttemeptingMovement != EntityToCheck)
		{
			if (EntityToCheck->GetIsBlockingEntity() &&
				(((TopLeftVertex.YComponent >= EntityToCheck->GetEntityBottomLeftVertex().YComponent) 
				&& (TopLeftVertex.YComponent <= EntityToCheck->GetEntityTopLeftVertex().YComponent)) || 
				((TopRightVertex.YComponent >= EntityToCheck->GetEntityBottomRightVertex().YComponent)
				&& (TopRightVertex.YComponent <= EntityToCheck->GetEntityTopRightVertex().YComponent))))
			{
				// Make sure the entity is close enough to block the Player:
				switch (MovementDirection)
				{
					// Hence: Only return from this function if this is the case:
				case ED_UPWARDS:
					if ((TopLeftVertex.YComponent >= EntityToCheck->GetEntityBottomLeftVertex().YComponent) &&
						(TopLeftVertex.YComponent <= EntityToCheck->GetEntityTopLeftVertex().YComponent))
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
int GameCollisionSystem::GetEntityColumnNumber(GameEntity* EntityMoving)
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

Vector2D GameCollisionSystem::AttemptHorizontalMovement(std::vector<ValidStartEndPositions>
	ValidRowPositionRanges, Vector2D ProposedTargetPosition)
{
	// Only check the range for a particular row:
	int RowToCheck = ProposedTargetPosition.YComponent / BLOCK_DIMENSIONS.YComponent;
	
	// Get the lowest and highest points to check against (in this range of values):
	int LowestXValue = ValidRowPositionRanges[RowToCheck].StartEndPositions.XComponent;
	int HighestXValue = ValidRowPositionRanges[RowToCheck].StartEndPositions.YComponent;

	// Validate the Target Position if it is out of range
	// (binding it to the lowest or highest X-values):
	if (ProposedTargetPosition.XComponent <= LowestXValue)
	{
		ProposedTargetPosition.XComponent = LowestXValue;
	}
	else if (ProposedTargetPosition.XComponent >= HighestXValue)
	{
		ProposedTargetPosition.XComponent = HighestXValue;
	}

	// Return this target position (whether validation was required or not):
	return ProposedTargetPosition;
}

Vector2D GameCollisionSystem::AttemptVerticalMovement(std::vector<ValidStartEndPositions>
	ValidColumnPositionRanges, Vector2D ProposedTargetPosition, GameEntity* EntityAttemptingMovement)
{
	// Only check within the range for a particular column:
	int ColumnToCheck = ProposedTargetPosition.XComponent / BLOCK_DIMENSIONS.XComponent;

	// Get the lowest and highest points to check against (in this range of values):
	int LowestYValue = ValidColumnPositionRanges[ColumnToCheck].StartEndPositions.XComponent;
	int HighestYValue = ValidColumnPositionRanges[ColumnToCheck].StartEndPositions.YComponent;

	// Validate the Target Position if it is out of range
	// (binding it to the lowest or highest X-values):
	if (ProposedTargetPosition.YComponent <= LowestYValue)
	{
		ProposedTargetPosition.YComponent = LowestYValue;
	}
	else if (ProposedTargetPosition.YComponent >= HighestYValue)
	{
		ProposedTargetPosition.YComponent = HighestYValue;
	}

	/** 
		If there is a wall block, or another blocking GameEntity
		directly above EntityAttemptingMovement, when moving upwards,
		or there is a blocking GameEntity below this GameEntity,
		when falling, return the original position, otherwise; the 
		ProposedTargetPosition is valid.
	*/
	int VerticalMovementDirection = ProposedTargetPosition.YComponent 
		- EntityAttemptingMovement->GetEntityPosition().YComponent;

	// Attempting to ascend to the row above EntityAttemptingMovement's current row :
	if (VerticalMovementDirection < 0)
	{
		if (GameEntities[EntityAttemptingMovement->GetCurrentRow() - 1]
			[EntityAttemptingMovement->GetCurrentColumn()]->GetIsBlockingEntity())
		{
			return EntityAttemptingMovement->GetEntityPosition();
		}
		else
		{
			return ProposedTargetPosition;
		}
	}
	// Attempting to descend to the row below EntityAttemptingMovement's current row:
	else
	{
		if (GameEntities[EntityAttemptingMovement->GetCurrentRow() + 1]
			[EntityAttemptingMovement->GetCurrentColumn()]->GetIsBlockingEntity())
		{
			return EntityAttemptingMovement->GetEntityPosition();
		}
		else
		{
			return ProposedTargetPosition;
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
	Vector2D ProposedTopLeftVertex = Vector2D(ConsideredEntity->GetEntityTopLeftVertex().XComponent -
		ConsideredEntity->GetMovementSpeed(), ConsideredEntity->GetEntityTopLeftVertex().YComponent);

	Vector2D ProposedTopRightVertex = Vector2D(ConsideredEntity->GetEntityTopRightVertex().XComponent +
		ConsideredEntity->GetMovementSpeed(), ConsideredEntity->GetEntityTopRightVertex().YComponent);

	if (!AnotherGameEntityOccupiesRangeBetweenPoints(ConsideredEntity, ProposedTopLeftVertex,
		ProposedTopRightVertex, ED_UPWARDS))
	{
		return true;
	}
	else
	{
		return false;
	}
}
