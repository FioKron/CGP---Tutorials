#include "GameEntity.h"
#include <iostream> // For debugging

// Standard constructor:
GameEntity::GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
	Vector2D ActiveBlockDimensions, Vector2D NewScreenDimensions, 
	EntityID UniqueEntityID, bool UsesTransparency)
{
	UniqueID = UniqueEntityID;
	CurrentGameLevelBlockDimensions = ActiveBlockDimensions;
	EntityRepresentation = new GameBitmap(RendererToUse, FileName, XPosition, YPosition, NewScreenDimensions, UsesTransparency);

	// Set BlockingEntity to the appropirate value:
	switch (UniqueEntityID)
	{
	// Enemy Doors, as well as Blank Blocks, are not blocking entities:
	case EI_BLANK_BLOCK:
	case EI_ENEMY_DOOR:
		BlockingEntity = false;
		break;

	// Otherwise...
	default:
		BlockingEntity = true;
		break;
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
bool GameEntity::BlockingGameEntityOccupiesPosition(Vector2D StartingVertex, Vector2D EndingVertex,
	EntityMovementDirection MovementDirection)
{
	// Only perform execution of this function; if this Entity is a blocking-entity:
	if (BlockingEntity)
	{
		switch (MovementDirection)
		{

		case ED_LEFTWARDS:
			if (PointsOverlapRightHandSide(StartingVertex, EndingVertex))
			{
				return true;
			}
			else
			{
				return false;
			}
			break;

		case ED_RIGHTWARDS:
			if (PointsOverlapLeftHandSide(StartingVertex, EndingVertex))
			{
				return true;
			}
			else
			{
				return false;
			}
			break;

		case ED_UPWARDS:
			if (PointsOverlapBottomSide(StartingVertex, EndingVertex))
			{
				return true;
			}
			else
			{
				return false;
			}
			break;

		default:
			break;
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

int GameEntity::GetMovementSpeed()
{
	return MOVEMENT_SPEED;
}

// For getting the top-left, top-right,
// bottom-left and bottom-right verticies:

// (This Entity's position is the top-left vertex)
Vector2D GameEntity::GetEntityTopLeftVertex()
{
	return GetEntityPosition();
}

Vector2D GameEntity::GetEntityTopRightVertex()
{
	return Vector2D(GetEntityTopLeftVertex().XComponent + GetEntityExtents().XComponent,
		GetEntityTopLeftVertex().YComponent);
}

Vector2D GameEntity::GetEntityBottomLeftVertex()
{
	return Vector2D(GetEntityTopLeftVertex().XComponent,
		GetEntityTopLeftVertex().YComponent + GetEntityExtents().YComponent);
}

Vector2D GameEntity::GetEntityBottomRightVertex()
{
	return Vector2D(GetEntityTopRightVertex().XComponent,
		GetEntityTopRightVertex().YComponent + GetEntityExtents().YComponent);
}

// Handle attempts at movement:
void GameEntity::AttemptMoveLeft()
{
	if (GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions.YComponent).CheckLeftSideCollision(this))
	{
		EntityRepresentation->MoveBitmapLeftwards(MOVEMENT_SPEED);
	}
}

void GameEntity::AttemptMoveRight()
{
	if (GameCollisionSystem::GetCollisionSystem(CurrentGameLevelBlockDimensions.YComponent).CheckRightSideCollision(this))
	{
		EntityRepresentation->MoveBitmapRightwards(MOVEMENT_SPEED);
	}
}

// Overlap checking:

bool GameEntity::PointsOverlapRightHandSide(Vector2D LineStartVertex, Vector2D LineEndVertex)
{
	// Local variable used for debugging purposes:
	bool RightHandSideOverlap = ((LineStartVertex.XComponent <= GetEntityTopRightVertex().XComponent) &&
		(LineStartVertex.YComponent >= GetEntityTopRightVertex().YComponent) &&
		(LineStartVertex.YComponent < GetEntityBottomRightVertex().YComponent)) ||
		((LineEndVertex.XComponent <= GetEntityBottomRightVertex().XComponent) &&
		(LineEndVertex.YComponent <= GetEntityBottomRightVertex().YComponent) &&
			(LineEndVertex.YComponent > GetEntityTopRightVertex().YComponent));

	return RightHandSideOverlap;
}

bool GameEntity::PointsOverlapLeftHandSide(Vector2D LineStartVertex, Vector2D LineEndVertex)
{
	// Local variable used for debugging purposes:
	bool LeftHandSideOverlap = ((LineStartVertex.XComponent >= GetEntityTopLeftVertex().XComponent) &&
		(LineStartVertex.YComponent >= GetEntityTopLeftVertex().YComponent) &&
		(LineStartVertex.YComponent < GetEntityBottomLeftVertex().YComponent)) ||
		((LineEndVertex.XComponent >= GetEntityBottomLeftVertex().XComponent) &&
		(LineEndVertex.YComponent <= GetEntityBottomLeftVertex().YComponent) &&
			(LineEndVertex.YComponent > GetEntityTopLeftVertex().YComponent));

	return LeftHandSideOverlap;
}

bool GameEntity::PointsOverlapBottomSide(Vector2D LineStartVertex, Vector2D LineEndVertex)
{
	// Local variable used for debugging purposes:
	bool BottomSideOverlap = ((LineStartVertex.YComponent >= GetEntityBottomLeftVertex().YComponent) &&
		(LineStartVertex.XComponent >= GetEntityBottomLeftVertex().XComponent) &&
		(LineStartVertex.XComponent < GetEntityBottomRightVertex().XComponent)) ||
		((LineEndVertex.YComponent >= GetEntityBottomRightVertex().YComponent) &&
		(LineEndVertex.XComponent <= GetEntityBottomRightVertex().XComponent) &&
			(LineEndVertex.XComponent > GetEntityBottomLeftVertex().XComponent));

	return BottomSideOverlap;
}

// Update behavior:
void GameEntity::UpdateEntity()
{
	// Assume this GameEntity has moved, when UpdateEntity is called:
	EntityRepresentation->Draw(true);
}