#include "GameBitmap.h"
#include "SDL.h"
#include "SDL_render.h"

// Standard constructor:
GameBitmap::GameBitmap(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, int YPosition, bool UsesTransparency)
{
	ScreenPosition = Vector2D(XPosition, YPosition);
	BitmapRenderer = RendererToUse;

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
void GameBitmap::Draw(int NewPositionX, int NewPositionY) 
{
	ScreenPosition.XComponent = NewPositionX;
	ScreenPosition.YComponent = NewPositionY;

	if (BitmapTexture)
	{
		SDL_Rect DestinationRectangle = { ScreenPosition.XComponent, ScreenPosition.YComponent, BitmapSurface->w, BitmapSurface->h };
		SDL_RenderCopy(BitmapRenderer, BitmapTexture, NULL, &DestinationRectangle);
	}
}
