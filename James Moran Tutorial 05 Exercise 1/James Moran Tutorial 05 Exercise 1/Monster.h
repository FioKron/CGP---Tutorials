#pragma once
#include "Bitmap.h"

class Monster
{
public:

	// Functions:

	Monster(SDL_Renderer* RendererToUse, std::string FileName, int XPosition, int YPosition, bool UsesTransparency = false);
	~Monster();
	
	/** For drawing the Bitmap of the monster */
	Bitmap* GetMonsterRepresenation();

protected:

	// Properties:

	Bitmap* MonsterRepresentation;
};

