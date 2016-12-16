#pragma once
#include "GameEntity.h"

class Monster : public GameEntity
{
public:

	// Functions:

	Monster(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName = "assets/monsterTrans.bmp", bool UsesTransparency = true);
};

