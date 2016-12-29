#include "GameEntity.h"

GameEntity::GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
	EntityID UniqueEntityID, bool UsesTransparency)
{
	//EntityScreenPosition = Vector2D(XPosition, YPosition);
	UniqueID = UniqueEntityID;
	EntityRepresentation = new GameBitmap(RendererToUse, FileName, XPosition, YPosition, UsesTransparency);
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

Vector2D GameEntity::GetEntityExtents()
{
	return EntityRepresentation->GetBitmapWidthHeight();
}

EntityID GameEntity::GetUniqueID()
{
	return UniqueID;
}

// Update behavior:
void GameEntity::UpdateEntity()
{
	// Assume this GameEntity has moved, when UpdateEntity is called:
	EntityRepresentation->Draw(true);
}