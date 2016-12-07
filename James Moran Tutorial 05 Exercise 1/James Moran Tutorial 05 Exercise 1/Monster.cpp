#include "Monster.h"

// Standard constructor:
/**Monster::Monster(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, bool UsesTransparency)
{
	__super::Bitmap(RendererToUse, FileName, XPosition, YPosition, UsesTransparency);
}
*/

Monster::Monster(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, bool UsesTransparency)
{
	MonsterXPosition = XPosition;
	MonsterYPosition = YPosition;
	__super::Bitmap(RendererToUse, FileName, XPosition, YPosition, UsesTransparency);
}
// Standard Destructor:
Monster::~Monster()
{
	delete this;
}

// Call the draw method in the Super class:
void Monster::Draw(int NewPositionX, int NewPositionY)
{
	MonsterXPosition = NewPositionX;
	MonsterYPosition = NewPositionY;
	__super::Draw(NewPositionX, NewPositionY);
}

/**
	Get methods with validation:
*/
int Monster::GetMonsterXPosition()
{
	if (MonsterXPosition)
	{
		return MonsterXPosition;
	}
}

int Monster::GetMonsterYPosition()
{
	if (MonsterYPosition)
	{
		return MonsterYPosition;
	}
}


