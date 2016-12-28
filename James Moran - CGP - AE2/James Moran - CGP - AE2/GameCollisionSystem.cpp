#include "GameCollisionSystem.h"

// For initialisation:
GameCollisionSystem::GameCollisionSystem()
{

}

// For cleaning up:
GameCollisionSystem::~GameCollisionSystem()
{
	for each (GameEntity* FocusedEntity in GameEntities)
	{
		delete FocusedEntity;
		FocusedEntity = nullptr;
	}
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
	return false;
}

bool GameCollisionSystem::CheckRightSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveX)
{
	return false;
}

bool GameCollisionSystem::CheckTopSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveY)
{
	return false;
}
