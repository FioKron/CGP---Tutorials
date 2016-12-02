#pragma once

#include <string>

// Foward declaration of certain structs:
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Bitmap
{

protected:

	// Keep in mind that; 'M_', could receive usage to identify a class member:
	SDL_Surface*	M_PBitmapSurface;
	SDL_Texture*	M_PBitmapTexture;
	SDL_Renderer*	M_PRenderer;

	// These are for the position of the Bitmap:
	int M_PositionX;
	int M_PositionY;

public:
	Bitmap(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, int YPosition, bool UsesTransparency = false);
	~Bitmap();

	/**
		Description: Draw this bitmap:

		@Params:

		int NewPositionX: The new X-Position for this Bitmap. (Tutorial 4, Exercise 1)
		int NewPositionY: The new Y-Position for this Bitmap. (Tutorial 4, Exercise 1)
	*/
	void Draw(int NewPositionX, int NewPositionY);
};

