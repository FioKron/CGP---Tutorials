#include "Monster.h"

// Standard constructor:
Monster::Monster(SDL_Renderer * RendererToUse, std::string FileName, int XPosition, int YPosition, bool UsesTransparency)
{
	if (!MonsterRepresentation)
	{
		MonsterRepresentation = new Bitmap(RendererToUse, FileName, XPosition, YPosition, UsesTransparency);
	}
}

// Standard Destructor:
Monster::~Monster()
{
	if (MonsterRepresentation)
	{
		delete MonsterRepresentation;
		MonsterRepresentation = nullptr; 
	}
}

Bitmap* Monster::GetMonsterRepresenation()
{
	if (MonsterRepresentation)
	{
		return MonsterRepresentation;
	}
}
