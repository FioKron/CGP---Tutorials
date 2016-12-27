#include "GameEntity.h"

GameEntity::GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
	bool UsesTransparency)
{
	EntityScreenPosition = Vector2D(XPosition, YPosition);
	PreviousEntityScreenPosition = EntityScreenPosition;
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

int GameEntity::GetEntityXPosition()
{
	return EntityScreenPosition.XComponent;
}

int GameEntity::GetEntityYPosition()
{
	return EntityScreenPosition.YComponent;
}

// For displaying this Entity:
void GameEntity::Draw()
{
	EntityRepresentation->Draw(EntityScreenPosition.XComponent, EntityScreenPosition.YComponent);
}

// Update behavior:
void GameEntity::UpdateEntity()
{
	Draw();
}

GameBitmap* GameEntity::GetEntityRepresentation()
{
	if (EntityRepresentation)
	{
		return EntityRepresentation;
	}
}

void GameEntity::CleanUpPreviousPosition()
{
	PreviousEntityScreenPosition = EntityScreenPosition;
	//EntityRepresentation->ClearSpace(PreviousEntityScreenPosition);
}
