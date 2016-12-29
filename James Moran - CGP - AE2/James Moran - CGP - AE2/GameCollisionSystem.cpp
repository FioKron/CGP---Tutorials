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
	// To return false if at the end:
	int ElementsChecked = 0;
	// The greatest value of ElementsChecked will always have equality to the size
	// of GameEntites, minus 1, so Elements to check is set to that value (for when checking is to stop): 
	int ElementsToCheck = GameEntities.size() - 1; 

	// COLAPSE INTO FUNCTIONS:
	for each (GameEntity* ConsideredEntity in GameEntities)
	{
		if (ConsideredEntity)
		{
			// Only check for position-occupation; if the EntityMoving is not the ConsideredEntity:
			if (EntityMoving != ConsideredEntity)
			{
				if (MovementDirection == Leftwards)
				{
					Vector2D ConsideredEntityTopRightCorner = Vector2D(ConsideredEntity->GetEntityPosition().XComponent + ConsideredEntity->GetEntityExtents().XComponent,
						ConsideredEntity->GetEntityPosition().YComponent);
					Vector2D ConsideredEntityBottomRightCorner = Vector2D(ConsideredEntityTopRightCorner.XComponent,
						ConsideredEntityTopRightCorner.YComponent + ConsideredEntity->GetEntityExtents().YComponent);

					/**
					Now check if ConsideredEntity's range (TopRightCorner.YComponent to BottomRightCorner.YComponent),
					matches EntityMoving's range (ProposedNewPoint1.YComponent to ProposedNewPoint2.YComponent):
					*/
					if ((ProposedNewPoint1.XComponent < ConsideredEntityTopRightCorner.XComponent) &&
						(ProposedNewPoint1.YComponent > ConsideredEntityTopRightCorner.YComponent) &&
						(ProposedNewPoint1.YComponent < ConsideredEntityBottomRightCorner.YComponent))
					{
						return true;
					}
					else if ((ProposedNewPoint2.XComponent < ConsideredEntityTopRightCorner.XComponent) &&
						(ProposedNewPoint2.YComponent > ConsideredEntityTopRightCorner.YComponent) &&
						(ProposedNewPoint2.YComponent < ConsideredEntityBottomRightCorner.YComponent))
					{
						return true;
					}					
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		ElementsChecked++;

		if (ElementsChecked == ElementsToCheck)
		{
			return false;
		}

		std::cout << ElementsChecked << std::endl;
	}

	// No entities occupy the space:
	return false;
}

// For adding Entities to this collection, for future collision reference checking:
void GameCollisionSystem::AddGameEntityToCollection(GameEntity* EntityToAdd)
{
	GameEntities.push_back(EntityToAdd);
}

/** 
	Check for collision on the left, right and top 
	sides respectivley.
*/
bool GameCollisionSystem::CheckLeftSideCollision(GameEntity* ConsideredEntity, int ProposedNewNegativeX)
{
	// For evauluating collision:
	Vector2D EntityWidthHeight = ConsideredEntity->GetEntityExtents();
	Vector2D NewTopLeftCorner = Vector2D(ProposedNewNegativeX, ConsideredEntity->GetEntityPosition().YComponent);
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

bool GameCollisionSystem::CheckRightSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveX)
{
	return false;
}

bool GameCollisionSystem::CheckTopSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveY)
{
	return false;
}
