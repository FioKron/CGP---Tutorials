//#pragma once - Include guards are used instead
#include "GameBitmap.h"
#include "GameLevel.h"

// For collections:
#include <vector>

// Foward declared-classes:
// (Hmm...)
class GameBitmap;

struct ValidStartEndPositions;

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

	/** For range checking (of the x-component) */
	bool IsThisVectorInRangeOfAnotherVectorAlongXAxis(Vector2D OtherVector, int Range)
	{
		if (this->YComponent == OtherVector.YComponent)
		{
			int FurthestNegativeX = this->XComponent - Range;
			int FurthestPositiveX = this->XComponent + Range;

			if ((OtherVector.XComponent >= FurthestNegativeX) && (OtherVector.XComponent <= FurthestPositiveX))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	// Overloaded operators:

	/** 
		For if either the X or Y Component values of this Vector, 
		are not equal to Target's X or Y Component values 
	*/
	bool Vector2D::operator!=(const Vector2D& Target)
	{
		if ((this->XComponent != Target.XComponent) || (this->YComponent != Target.YComponent))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Vector2D::operator==(const Vector2D& Target)
	{
		if ((this->XComponent == Target.XComponent) && (this->YComponent == Target.YComponent))
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
	EI_ENEMY_DOOR,
	EI_LEVEL_EXIT_DOOR,
	EI_HIGHEST_ENEMY,
	EI_LOWEST_ENEMY,
	EI_PLAYER
};
#endif

#ifndef ENTITY_MOVEMENT_DIRECTION
#define ENTITY_MOVEMENT_DIRECTION
enum EntityMovementDirection
{
	ED_LEFTWARDS,
	ED_RIGHTWARDS,
	ED_UPWARDS,
	ED_DOWNWARDS
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
		Vector2D ActiveBlockDimensions, Vector2D NewScreenDimensions, EntityID UniqueEntityID,
		std::vector<ValidStartEndPositions> NewValidMobileEntityRowMovementValues,
		std::vector<std::vector<ValidStartEndPositions>> NewValidMobileEntityColumnMovementValues, bool UsesTransparency = false);

	/** Default constructor (for 'empty' initialisation) */
	GameEntity();
	
	/** Standard destructor */
	~GameEntity();

	/**
		For updating this Entity 
		(The Player overrides this function;
		to handle falling whilst airborne)
	*/
	virtual void UpdateEntity();

	/**
		Description: Check if there is a blocking-GameEntity
		at PositionToCheck.

		@Params: Vector2D StartingVertex: The position to check from
		
		Vector2D EndingVertex: The position to check to.

		EntityMovementDirection MovementDirection: The direction another
		Entity is attemepting to move in.

		@Return: bool PositionOccupied: True if there is a
		blocking GameEntity here.
	*/
	bool BlockingGameEntityOccupiesPosition(Vector2D StartingVertex, Vector2D EndingVertex,
		EntityMovementDirection MovementDirection);

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

	int GetMovementSpeed();

	/** For movement in general and movement validation */
	std::vector<ValidStartEndPositions> GetValidMobileEntityRowMovementValues();
	std::vector<std::vector<ValidStartEndPositions>> GetValidMobileEntityColumnMovementValues();

	/** For reference to the row and column of this GameEntity */
	int GetCurrentRow();
	int GetCurrentColumn();

	/**
	To get the top-left, top-right,
	bottom-left and bottom right verticies
	of this GameEntity's bounding-box
	(respectivley).

	@Return: Vector2D: The respective vertex,
	of this GameEntity's bounding-box.
	*/
	Vector2D GetEntityTopLeftVertex();
	Vector2D GetEntityTopRightVertex();
	Vector2D GetEntityBottomLeftVertex();
	Vector2D GetEntityBottomRightVertex();

	/** 
		Description: For movement handling (common amongst all types of mobile entities).

		@Param: EntityMovementDirection MovementDirection: The intended positive, or
		negative movement direction, along the respective axis (X or Y respectivley).
	*/
	void AttemptHorizontalMovement(EntityMovementDirection MovementDirection);
	void AttemptVerticalMovement(EntityMovementDirection MovementDirection);

protected:

	// Properties:

	// Constant values:

	const int MOVEMENT_SPEED = 3;

	// Functions:

	/**
	Description: Check if a vertex overlaps
	the left-hand-side or right-hand-sidem
	of this GameEntity's bounding-box
	(respectivley).

	@Param: Vector2D VertexToCheck:
	The vertex to check for overlap,
	on the right or left sides of this
	GameEntity's bounding-box.

	@Return: bool VertexOverlapsSide:
	True if this is the case.
	*/
	bool PointsOverlapRightHandSide(Vector2D LineStartVertex, Vector2D LineEndVertex);
	bool PointsOverlapLeftHandSide(Vector2D LineStartVertex, Vector2D LineEndVertex);
	bool PointsOverlapBottomSide(Vector2D LineStartVertex, Vector2D LineEndVertex);

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

	/** 
		A map of the area a mobile-entity can move in 
		(for both the rows and the columns)
	*/
	std::vector<ValidStartEndPositions> ValidMobileEntityRowMovementValues;
	std::vector<std::vector<ValidStartEndPositions>> ValidMobileEntityColumnMovementValues;
};
#endif
