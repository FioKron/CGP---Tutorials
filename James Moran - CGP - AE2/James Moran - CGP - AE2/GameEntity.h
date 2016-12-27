#pragma once
#include "GameBitmap.h"

class GameEntity
{
public:

	// Functions:

	GameEntity(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, 
		bool UsesTransparency = false);
	~GameEntity();

	/** 
		For drawing the Bitmap of this entity in the correct
		on-screen location
	*/
	int GetEntityXPosition();
	int GetEntityYPosition();

	/**
		Description: Draw this Entity's bitmap.
	*/
	void Draw();

	/** For updating this Entity */
	void UpdateEntity();

	// Other get methods:

	/** For calling to GameBitmap */
	GameBitmap* GetEntityRepresentation();

protected:

	// Properties:

	GameBitmap* EntityRepresentation;
		
	// For use in drawing:

	Vector2D EntityScreenPosition;

	/** Clean-up the bitmap from its previous position */
	void CleanUpPreviousPosition();

	/** The location of this Entity in the previous frame */
	Vector2D PreviousEntityScreenPosition;
};

