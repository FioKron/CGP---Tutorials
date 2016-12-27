#pragma once

#include <string>
#include "SDL.h"

// Structures:

/** For a 2D vector */
struct Vector2D
{
	int XComponent;
	int YComponent;

	/** The standard constructor for this struct */
	Vector2D(int NewXComponent, int NewYComponent)
	{
		XComponent = NewXComponent;
		YComponent = NewYComponent;
	}

	// Default Constructor:
	Vector2D()
	{

	}

	/** For scalar incrementation */
	void ScalarIncrementVector(int IncrementationValue)
	{
		XComponent += IncrementationValue;
		YComponent += IncrementationValue;
	}
};

class GameBitmap
{
	
private:

	// Keep in mind that; 'M_', could receive usage to identify a class member
	SDL_Surface* BitmapSurface;
	SDL_Texture* BitmapTexture;
	SDL_Renderer* BitmapRenderer;

	// Position on the grid (from the top left)
	Vector2D ScreenPosition;

	// Its extents
	Vector2D BitmapWidthHeight;

public:
	GameBitmap(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, int YPosition, bool UsesTransparency = false);
	~GameBitmap();

	/**
		Description: Draw this bitmap.

		@Params:

		int NewPositionX: The new X-Position for this Bitmap. (Tutorial 4, Exercise 1)
		int NewPositionY: The new Y-Position for this Bitmap. (Tutorial 4, Exercise 1)
	*/
	void Draw(int NewPositionX, int NewPositionY);
};

