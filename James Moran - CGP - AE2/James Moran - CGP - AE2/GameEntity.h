#pragma once
#include "GameBitmap.h"

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

enum EntityID
{
	WallBlockID,
	EnemyID,
	PlayerID
};

class GameEntity
{

public:

	// Functions:

	GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
		EntityID UniqueEntityID, bool UsesTransparency = false);
	~GameEntity();

	/** For updating this Entity */
	void UpdateEntity();

	// Get methods:

	/**
		For drawing the Bitmap of this entity in the correct
		on-screen location
	*/
	Vector2D GetEntityPosition();

	Vector2D GetEntityExtents();

	EntityID GetUniqueID();

protected:

	// Properties:

	GameBitmap* EntityRepresentation;

	/** To uniquely identify this GameEntity */
	EntityID UniqueID;
		
	// For use in drawing:
	
	//Vector2D EntityScreenPosition;
};

