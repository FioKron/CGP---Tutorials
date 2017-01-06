#include "EnemyDoor.h"

EnemyDoor::EnemyDoor(SDL_Renderer * RendererToUse, int XPosition, int YPosition, Vector2D ActiveBlockDimensions, 
	Vector2D NewScreenDimensions, EntityID UniqueID, std::string FileName) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, ActiveBlockDimensions, NewScreenDimensions, UniqueID)
{
	PatrolRouteCovered = false;
}

EnemyDoor::~EnemyDoor()
{

}

bool EnemyDoor::GetPatrolRouteCovered()
{
	return PatrolRouteCovered;
}

void EnemyDoor::PatrolRouteReceivedCoverage()
{
	PatrolRouteCovered = true;
}

void EnemyDoor::PatrolRouteNotCovered()
{
	PatrolRouteCovered = false;
}
