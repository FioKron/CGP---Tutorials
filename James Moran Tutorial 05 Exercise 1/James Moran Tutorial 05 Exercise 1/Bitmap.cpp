#include "Bitmap.h"
#include "SDL.h"
#include "SDL_render.h"

Bitmap::Bitmap(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, int YPosition, bool UsesTransparency)
{
	// Have Bitmap keep onto the renderer to use:
	M_PRenderer = RendererToUse;

	// Initilise the Bitmap surface:
	M_PBitmapSurface = SDL_LoadBMP(FileName.c_str());

	// Error handling:
	if (!M_PBitmapSurface)
	{
		printf("Surface for Bitmap '%s' not loaded!\n", FileName.c_str());
		printf("%s\n", SDL_GetError());
	}
	else
	{
		/** 
			When using transparency, it is assumed that the 
			colour key is magenta (at least in 
			this case: Red = 255, Green = 0, Blue = 255):
		*/
		if (UsesTransparency)
		{
			Uint32 ColourKey = SDL_MapRGB(M_PBitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(M_PBitmapSurface, SDL_TRUE, ColourKey);
		}

		// Initilise the texture:
		M_PBitmapTexture = SDL_CreateTextureFromSurface(M_PRenderer, M_PBitmapSurface);

		// Handle errors here too:
		if (!M_PBitmapTexture)
		{
			printf("Texture for Bitmap '%s' not loaded!\n", FileName.c_str());
			printf("%s\n", SDL_GetError());
		}
	}

	// For the position:
	M_PositionX = XPosition;
	M_PositionY = YPosition;
}

Bitmap::Bitmap()
{

}

Bitmap::~Bitmap()
{
	// Apparently; 'good practice is to destroy in the reverse order in which it was created.':
	if (M_PBitmapTexture)
	{
		SDL_DestroyTexture(M_PBitmapTexture);
	}

	if (M_PBitmapSurface)
	{
		SDL_FreeSurface(M_PBitmapSurface);
	}
}

void Bitmap::Draw(int NewPositionX, int NewPositionY) 
{
	// Update this bitmap's current position:
	M_PositionX = NewPositionX;
	M_PositionY = NewPositionY;

	// Render the Bitmap at the respective co-ordinates:
	if (M_PBitmapTexture)
	{
		SDL_Rect DestinationRectangle = { M_PositionX, M_PositionY, M_PBitmapSurface->w, M_PBitmapSurface->h };
		SDL_RenderCopy(M_PRenderer, M_PBitmapTexture, NULL, &DestinationRectangle);
	}
}
