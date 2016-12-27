#include "Enemy.h"

Enemy::Enemy(SDL_Renderer * RendererToUse, Vector2D NewPatrolEndPoint, int XPosition, int YPosition, std::string FileName, bool UsesTransparency) :
	GameEntity(RendererToUse, XPosition, YPosition, FileName, UsesTransparency)
{
	PatrolStartPoint = Vector2D(XPosition, YPosition);
	PatrolEndPoint = Vector2D(NewPatrolEndPoint);
}