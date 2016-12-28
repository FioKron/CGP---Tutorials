#include "GameEntity.h"

GameEntity::GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
	bool UsesTransparency)
{
	EntityScreenPosition = Vector2D(XPosition, YPosition);
	EntityRepresentation = new GameBitmap(RendererToUse, FileName, EntityScreenPosition.XComponent, EntityScreenPosition.YComponent, UsesTransparency);
}

GameEntity::~GameEntity()
{
	if (EntityRepresentation)
	{
		delete EntityRepresentation;
		EntityRepresentation = nullptr;
	}
}

/**
	Get methods:
*/
Vector2D GameEntity::GetEntityPosition()
{
	return EntityRepresentation->GetBitmapPosition();
}

// Update behavior:
void GameEntity::UpdateEntity()
{
	EntityRepresentation->Draw(true);
}