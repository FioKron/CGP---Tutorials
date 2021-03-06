#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "GameCollisionSystem.h"

// Forward declarations...
struct ValidStartEndPositions;

// Structures:

/** 
	For a 2D vector 

	An older version, as VECTOR2D would not have to receive
	definition in full here (as the definition in GameEntity.h 
	takes precedance).
*/
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

	bool Vector2D::operator!=(const Vector2D& Target)
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

class GameBitmap
{
	
private:

	// Properties:

	// Keep in mind that; 'M_', could receive usage to identify a class member
	SDL_Surface* BitmapSurface;
	SDL_Texture* BitmapTexture;
	SDL_Renderer* BitmapRenderer;

	// 'blank' properties
	SDL_Surface* BlankSurface;
	SDL_Texture* BlankTexture;

	// Pixel position on the screen (from the top left)
	Vector2D BitmapScreenPosition;

	// Its extents
	Vector2D BitmapWidthHeight;

	// Screen dimensions (to make sure a texture is not drawn off screen)
	Vector2D GameScreenDimensions;

	// Flags:
	
	/** For ease in reducing flickering */
	bool BitmapDrawnOnce;

	// Functions:

	/** Draw the BitmapTexture of this GameBitmap */
	void DrawBitmapTexture();

	/** Clear the BitmapTexture of this GameBitmap*/
	void ClearBitmapTexture();

	/**
		Description: Only draw this GameBitmap, if the GameEntity using this, has moved
		since the last Draw() call. 

		@Params: Vector2D ProposedPosition: The intended new location for this bitmap.
	*/
	bool IsNewPositionDifferentToOldPosition(Vector2D ProposedPosition);

public:
	GameBitmap(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, int YPosition, 
		Vector2D NewScreenDimensions, bool UsesTransparency = false);
	~GameBitmap();

	/**
		Description: Draw this bitmap.

		@Param: bool GameEntityHasMovedSinceLastDraw: For if the
		bitmap of this GameEntity has moved since the last call to
		Draw().
	*/
	void Draw(bool GameEntityHasMovedSinceLastDraw);

	// Get methods:

	Vector2D GetBitmapPosition();

	Vector2D GetBitmapWidthHeight();

	// Validated set methods:

	void SetBitmapPosition(Vector2D NewPosition);

	// Update methods:

	/** 
		Description: Move bitmaps by the movement speed of 
		the GameEntity (in the respective direction).

		@Param: int MovementSpeed: to number of pixels to move
		along the respective axis by (positive for rightwards
		and downwards movement, or negative for leftwards and
		upwards movement, in the order of definition).
	*/
	void MoveBitmapHorizontally(int MovementSpeed, std::vector<ValidStartEndPositions> ValidXPositions);
	void MoveBitmapVertically(int MovementSpeed, std::vector<ValidStartEndPositions> ValidYPositions);

	/** 
		Description: To validate this bitmap's position, keeping
		its position's X-Component values, within the highest and 
		lowest X values.

		@Params: int LowestXValue: The lowest value in this range, 
		to keep this bitmap's position's XComponent within.

		int HighestXValue: The highest value in this range, to keep
		this bitmap's position's XComponent within.
	*/
	void ValidateXPosition(int LowestXValue, int HighestXValue);
};