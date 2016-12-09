#pragma once
#include "Bitmap.h"

class Monster : public Bitmap
{
public:

	// Functions:

	Monster(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName = "assets/monsterTrans.bmp", bool UsesTransparency = true);
	~Monster();
	
	/** For drawing the Bitmap of the monster */
	//Bitmap* GetMonsterRepresenation();
	int GetMonsterXPosition();
	int GetMonsterYPosition();
	
	/**
	Description: Draw this Monster:

	@Params:

	int NewPositionX: The new X-Position for this Bitmap. (Tutorial 4, Exercise 1)
	int NewPositionY: The new Y-Position for this Bitmap. (Tutorial 4, Exercise 1)
	*/
	void Draw(int NewPositionX, int NewPositionY)override;

protected:

	// Properties:

	//Bitmap* MonsterRepresentation;
	int MonsterXPosition;
	int MonsterYPosition;
};

