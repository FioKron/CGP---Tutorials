//#pragma once
#include "GameBitmap.h"
#include "GameLevel.h"

// Foward declared-classes:
// (Hmm...)
class GameBitmap;

// FOR AN UNKNOWN REASON, EVEN THOUGH IT IS DEFINED IN GameBitmap.h,
// THE INCLUDE-GUARDS ARE STILL REQUIRED HERE, FOR GameEntity TO 
// RECOGNISE THIS STRUCTURE!"3/

/** For a 2D vector */
#ifndef VECTOR2D
#define VECTOR2D
struct Vector2D
{
	// Properties:

	int XComponent;
	int YComponent;

	// Functions:

	/** The standard constructor for this struct */
	Vector2D(int NewXComponent, int NewYComponent)
	{
		XComponent = NewXComponent;
		YComponent = NewYComponent;
	}

	/** Default Constructor: */
	Vector2D()
	{

	}

	/** For scalar incrementation */
	void ScalarIncrementVector(int IncrementationValue)
	{
		XComponent += IncrementationValue;
		YComponent += IncrementationValue;
	}

	// Overloaded operators:

	bool Vector2D::operator!=(const Vector2D& Target)
	{
		if ((this->XComponent != Target.XComponent) && (this->YComponent != Target.YComponent))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
#endif

// Enumerations:
#ifndef ENTITY_ID
#define ENTITY_ID
enum EntityID
{
	EI_BLANK_BLOCK,
	EI_WALL_BLOCK,
	EI_ENEMY,
	EI_PLAYER
};
#endif

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class GameEntity
{
	
public:

	// Functions:

	/**
		Description: Standard constructor.

		@Params: SDL_Renderer* RendererToUse: The renderer to use for this Entity.
		int XPosition: The new X-Position of this entity (in pixels).
		int YPosition: The new Y-Position of this entity (in pixels).
		std::string FileName: The file name and relative path, of the bitmap for
		this GameEntity to load.
		EntityID UniqueEntityID: The unique ID of this Entity, for identification in
		other class's functions.
		Vector2D ActiveBlockDimensions: For the dimensions of each block, of the level,
		this GameEntity is currently within (for determining where in the grid mobile-entities are).
		bool UsesTransparency = false: As the majority of game-entities will not use a transparency
		layer (can set so that this is not the case (not-not, that is)).
	*/
	GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
		Vector2D ActiveBlockDimensions, EntityID UniqueEntityID, bool UsesTransparency = false);

	/** Default constructor (for 'empty' initialisation) */
	GameEntity();
	
	/** Standard destructor */
	~GameEntity();

	/** For updating this Entity */
	void UpdateEntity();

	/**
		Description: Check if there is a blocking-GameEntity
		at PositionToCheck.

		@Param: Vector2D StartingVertex: The position to check from
		Vector2D EndingVertex: The position to check to.

		@Return: bool PositionOccupied: True if there is a
		blocking GameEntity here.
	*/
	bool BlockingGameEntityOccupiesPosition(Vector2D StartingVertex, Vector2D EndingVertex);

	// Get methods:

	/**
		For drawing the Bitmap of this entity in the correct
		on-screen location
	*/
	Vector2D GetEntityPosition();

	Vector2D GetEntityExtents();

	EntityID GetUniqueID();

	Vector2D GetGameLevelBlockDimensions();

	bool GetIsBlockingEntity();

protected:

	// Properties:

	GameBitmap* EntityRepresentation;

	/** To uniquely identify this GameEntity */
	EntityID UniqueID;

	// Flags:

	bool BlockingEntity;

	/** 
		Dimensions of each block within the
		active level (for collision checking later) 
	*/
	Vector2D CurrentGameLevelBlockDimensions;
		
	// For use in drawing:
	
	//Vector2D EntityScreenPosition;
};
#endif
