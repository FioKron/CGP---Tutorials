#pragma once

#include <string>

// Foward declaration of certain structs:
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Bitmap
{

private:

	// Keep in mind that; 'M_', could receive usage to identify a class member:
	SDL_Surface*	M_PBitmapSurface;
	SDL_Texture*	M_PBitmapTexture;
	SDL_Renderer*	M_PRenderer;

	// I presume that these are for the position of the Bitmap:
	int M_PositionX;
	int M_PositionY;

public:
	Bitmap(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, int YPosition, bool UsesTransparency = false);
	~Bitmap();

	void Draw();
};

