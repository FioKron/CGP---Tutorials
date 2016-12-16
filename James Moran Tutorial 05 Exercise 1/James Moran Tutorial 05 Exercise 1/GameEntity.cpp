#include "GameEntity.h"

GameEntity::GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, bool UsesTransparency)
{
	EntityXPosition = XPosition;
	EntityYPosition = YPosition;
	EntityRepresentation = new Bitmap(RendererToUse, FileName, EntityXPosition, EntityXPosition, UsesTransparency);
}

GameEntity::~GameEntity()
{
	if (EntityRepresentation)
	{
		delete EntityRepresentation;
	}
}

/**
	Get methods with validation:
*/

int GameEntity::GetEntityXPosition()
{
	if (EntityXPosition)
	{
		return EntityXPosition;
	}
	else
	{
		return NULL;
	}
}

int GameEntity::GetEntityYPosition()
{
	if (EntityYPosition)
	{
		return EntityYPosition;
	}
	else
	{
		return NULL;
	}
}

void GameEntity::Draw(int NewPositionX, int NewPositionY)
{
	// Update this bitmap's current position:
	EntityXPosition = NewPositionX;
	EntityYPosition = NewPositionY;

	EntityRepresentation->Draw(EntityXPosition, EntityYPosition);
}
