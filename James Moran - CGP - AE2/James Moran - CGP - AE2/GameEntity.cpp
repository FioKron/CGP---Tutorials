#include "GameEntity.h"
#include <iostream> // For debugging

// Standard constructor:
GameEntity::GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
	Vector2D ActiveBlockDimensions, EntityID UniqueEntityID, bool UsesTransparency)
{
	UniqueID = UniqueEntityID;
	CurrentGameLevelBlockDimensions = ActiveBlockDimensions;
	EntityRepresentation = new GameBitmap(RendererToUse, FileName, XPosition, YPosition, UsesTransparency);

	// Set BlockingEntity to the appropirate value:
	if (UniqueEntityID == EI_BLANK_BLOCK)
	{
		BlockingEntity = false;
	}
	else
	{
		BlockingEntity = true;
	}
}

// Default constructor:
GameEntity::GameEntity()
{

}

// Standard destructor:
GameEntity::~GameEntity()
{
	if (EntityRepresentation)
	{
		delete EntityRepresentation;
		EntityRepresentation = nullptr;
	}
}

// Check if this is the case:
bool GameEntity::BlockingGameEntityOccupiesPosition(Vector2D StartingVertex, Vector2D EndingVertex)
{
	// Only perform execution of this function; if this Entity is a blocking-entity:
	if (BlockingEntity)
	{
		// For readability:
		Vector2D EntityPosition = GetEntityPosition();
		Vector2D EntityExtents = GetEntityExtents();

		Vector2D EntityTopRightCorner = Vector2D(EntityPosition.XComponent + EntityExtents.XComponent,
			EntityPosition.YComponent);
		Vector2D EntityBottomRightCorner = Vector2D(EntityTopRightCorner.XComponent,
			EntityTopRightCorner.YComponent + EntityExtents.YComponent);

		std::cout << "Starting Vertex Overlaps: " + ((StartingVertex.XComponent <= EntityTopRightCorner.XComponent) &&
			(StartingVertex.YComponent >= EntityTopRightCorner.YComponent) &&
			(StartingVertex.YComponent < EntityBottomRightCorner.YComponent)) << std::endl;

		std::cout << "Ending Vertex Overlaps: " + ((EndingVertex.XComponent <= EntityTopRightCorner.XComponent) &&
			(EndingVertex.YComponent <= EntityTopRightCorner.YComponent) &&
			(EndingVertex.YComponent > EntityBottomRightCorner.YComponent)) << std::endl;

		if ((StartingVertex.XComponent <= EntityTopRightCorner.XComponent) &&
			(StartingVertex.YComponent >= EntityTopRightCorner.YComponent) &&
			(StartingVertex.YComponent < EntityBottomRightCorner.YComponent))
		{
			return true;
		}
		else if ((EndingVertex.XComponent <= EntityTopRightCorner.XComponent) &&
			(EndingVertex.YComponent <= EntityTopRightCorner.YComponent) &&
			(EndingVertex.YComponent > EntityBottomRightCorner.YComponent))
		{
			return true;
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

Vector2D GameEntity::GetGameLevelBlockDimensions()
{
	return CurrentGameLevelBlockDimensions;
}

bool GameEntity::GetIsBlockingEntity()
{
	return BlockingEntity;
}

// Update behavior:
void GameEntity::UpdateEntity()
{
	// Assume this GameEntity has moved, when UpdateEntity is called:
	EntityRepresentation->Draw(true);
}