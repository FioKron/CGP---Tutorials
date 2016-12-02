#pragma once
#include "Bitmap.h"

class Monster : Bitmap
{
public:

	// Functions:

	Monster(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName = "assets/monsterTrans.bmp", bool UsesTransparency = true);
	~Monster();
	
	/** For drawing the Bitmap of the monster */
	//Bitmap* GetMonsterRepresenation();
	//int GetMonsterXPosition();
	//int GetMonsterYPosition();

protected:

	// Properties:

	//Bitmap* MonsterRepresentation;
	//int MonsterXPosition;
	//int MonsterYPosition;
};

