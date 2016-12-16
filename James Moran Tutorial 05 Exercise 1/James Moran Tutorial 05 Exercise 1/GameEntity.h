#pragma once
#include "Bitmap.h"

class GameEntity
{
public:
	GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, bool UsesTransparency = false);
	~GameEntity();

	/** For drawing the Bitmap of the monster in the Game class */
	int GetEntityXPosition();
	int GetEntityYPosition();

	/**
	Description: Draw this Monster:

	@Params:

	int NewPositionX: The new X-Position for this Bitmap. (Tutorial 4, Exercise 1)
	int NewPositionY: The new Y-Position for this Bitmap. (Tutorial 4, Exercise 1)
	*/
	void Draw(int NewPositionX, int NewPositionY);

protected:

	// Properties:

	Bitmap* EntityRepresentation;
	int EntityXPosition;
	int EntityYPosition;
};

