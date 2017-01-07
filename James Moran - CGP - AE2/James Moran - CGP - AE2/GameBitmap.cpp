#include "GameBitmap.h"

// Standard constructor:
GameBitmap::GameBitmap(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, 
	int YPosition, Vector2D NewScreenDimensions, bool UsesTransparency)
{
	BitmapScreenPosition = Vector2D(XPosition, YPosition);
	BitmapRenderer = RendererToUse;
	BitmapDrawnOnce = false;
	// RESOLVE:
	BitmapWidthHeight = Vector2D(50, 50);

	GameScreenDimensions = NewScreenDimensions;

	// Initilise the GameBitmap surface:
	BitmapSurface = SDL_LoadBMP(FileName.c_str());
	
	if (!BitmapSurface)
	{
		printf("Surface for GameBitmap '%s' not loaded!\n", FileName.c_str());
		printf("%s\n", SDL_GetError());
	}
	// If the above is successful...
	else
	{
		//printf("%n %n", BitmapSurface->w, BitmapSurface->h);
		/** 
			Set-up the texture:

			(When using transparency, it is assumed that the 
			colour key is the deepest shade of purple (at least in 
			this case: Where Red = 255, Green = 0, Blue = 255)):
		*/
		if (UsesTransparency)
		{
			Uint32 ColourKey = SDL_MapRGB(BitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(BitmapSurface, SDL_TRUE, ColourKey);
		}

		BitmapTexture = SDL_CreateTextureFromSurface(BitmapRenderer, BitmapSurface);

		if (!BitmapTexture)
		{
			printf("Texture for GameBitmap '%s' not loaded! %s\n", FileName.c_str(), SDL_GetError());
			printf("%s\n", SDL_GetError());
		}
	}

	BlankSurface = SDL_CreateRGBSurface(0, BitmapScreenPosition.XComponent, BitmapScreenPosition.YComponent, 32, 0, 0, 0, 0);

	if (!BlankSurface)
	{
		printf("BlankSurface is invalid!%s\n", SDL_GetError());
		printf("%s\n", SDL_GetError());
	}
	else
	{
		// White for a blank space:
		Uint32 BlankColour = SDL_MapRGB(BlankSurface->format, 255, 255, 255);
		SDL_FillRect(BlankSurface, NULL, BlankColour);
		
		BlankTexture = SDL_CreateTextureFromSurface(BitmapRenderer, BlankSurface);

		if (!BitmapTexture)
		{
			printf("BlankTexture is invalid! %s\n", SDL_GetError());
			printf("%s\n", SDL_GetError());
		}
	}	
}

// Standard destructor:
GameBitmap::~GameBitmap()
{
	// (Apparently; 'good practice is to destroy in the reverse order in which it was created.'):
	if (BitmapTexture)
	{
		SDL_DestroyTexture(BitmapTexture);
	}

	if (BitmapSurface)
	{
		SDL_FreeSurface(BitmapSurface);
	}

	if (BitmapRenderer)
	{
		SDL_DestroyRenderer(BitmapRenderer);
	}
}

// For displaying this bitmap:
void GameBitmap::Draw(bool GameEntityHasMovedSinceLastDraw)
{
	if (!BitmapDrawnOnce)
	{
		// Draw the bitmap for the first time.
		DrawBitmapTexture();
		BitmapDrawnOnce = true;
	}

	if (BitmapTexture && GameEntityHasMovedSinceLastDraw)
	{
		// Update the position first...
		//BitmapScreenPosition.XComponent = NewPositionX;
		//BitmapScreenPosition.YComponent = NewPositionY;

		// ...clean-up next...		
		ClearBitmapTexture();

		// ...then draw on-top of this blank space:
		DrawBitmapTexture();
	}
}

// Get methods:

Vector2D GameBitmap::GetBitmapPosition()
{
	return BitmapScreenPosition;
}

Vector2D GameBitmap::GetBitmapWidthHeight()
{
	return BitmapWidthHeight;
}

// (Validated) set methods:

// For this method; The parameter's value is validated before this function is called
void GameBitmap::SetBitmapPosition(Vector2D NewPosition)
{
	if (NewPosition != BitmapScreenPosition)
	{
		BitmapScreenPosition = NewPosition;

		// Validation:
		if (BitmapScreenPosition.XComponent > GameScreenDimensions.XComponent)
		{
			BitmapScreenPosition.XComponent = GameScreenDimensions.XComponent;
		}

		if (BitmapScreenPosition.YComponent > GameScreenDimensions.YComponent)
		{
			BitmapScreenPosition.YComponent = GameScreenDimensions.YComponent;
		}
	}
	
}

// Movement of this bitmap as required:
void GameBitmap::MoveBitmapHorizontally(int MovementSpeed, std::vector<ValidStartEndPositions> ValidXPositions)
{
	BitmapScreenPosition.XComponent += MovementSpeed;

	// For this bitmap's current row:
	int RowToCheck = BitmapScreenPosition.YComponent / BitmapWidthHeight.YComponent;

	// Get the lowest and highest points for validation purposes (in this range of values):
	int LowestXValue = ValidXPositions[RowToCheck].StartEndPositions.XComponent;
	int HighestXValue = ValidXPositions[RowToCheck].StartEndPositions.YComponent;

	// Then validate this bitmap's XPosition:
	ValidateXPosition(LowestXValue, HighestXValue);
}

void GameBitmap::MoveBitmapVertically(int MovementSpeed, std::vector<ValidStartEndPositions> ValidYPositions)
{
	BitmapScreenPosition.YComponent += MovementSpeed;
}

void GameBitmap::ValidateXPosition(int LowestXValue, int HighestXValue)
{
	// Validate this Bitmap's screen-position if it is outside of 
	// the range from LowestXValue to HighestXValue:
	if (BitmapScreenPosition.XComponent <= LowestXValue)
	{
		BitmapScreenPosition.XComponent = LowestXValue;
	}
	else if (BitmapScreenPosition.XComponent >= HighestXValue)
	{
		BitmapScreenPosition.XComponent = HighestXValue;
	}
}

// Drawing and clearing the renderer:
void GameBitmap::DrawBitmapTexture()
{
	SDL_Rect BitmapDestinationRectangle = { BitmapScreenPosition.XComponent, BitmapScreenPosition.YComponent, BitmapSurface->w, BitmapSurface->h };
	SDL_RenderCopy(BitmapRenderer, BitmapTexture, NULL, &BitmapDestinationRectangle);
}

void GameBitmap::ClearBitmapTexture()
{
	SDL_Rect ClearDestinationRectangle = { BitmapScreenPosition.XComponent, BitmapScreenPosition.YComponent,
		BitmapWidthHeight.XComponent, BitmapWidthHeight.YComponent };
	SDL_RenderCopy(BitmapRenderer, BlankTexture, NULL, &ClearDestinationRectangle);
}

// Only draw the bitmap if the bitmap has received translation
bool GameBitmap::IsNewPositionDifferentToOldPosition(Vector2D ProposedPosition)
{
	if (BitmapScreenPosition != ProposedPosition)
	{
		return true;
	}
	else
	{
		return false;
	}
}
