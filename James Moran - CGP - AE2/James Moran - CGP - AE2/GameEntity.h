#pragma once
#include "GameBitmap.h"

class GameEntity
{
public:

	// Functions:

	GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
		bool UsesTransparency = false);
	~GameEntity();

	/** For updating this Entity */
	void UpdateEntity();

	// Get methods:

	/**
		For drawing the Bitmap of this entity in the correct
		on-screen location
	*/
	Vector2D GetEntityPosition();

protected:

	// Properties:

	GameBitmap* EntityRepresentation;
		
	// For use in drawing:

	Vector2D EntityScreenPosition;
};

