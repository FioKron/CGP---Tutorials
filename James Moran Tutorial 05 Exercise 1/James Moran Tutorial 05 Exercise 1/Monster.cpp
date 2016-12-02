#include "Monster.h"

// Standard constructor:
/**Monster::Monster(SDL_Renderer* RendererToUse, int XPosition, int YPosition, std::string FileName, bool UsesTransparency)
{
	__super::Bitmap(RendererToUse, FileName, XPosition, YPosition, UsesTransparency);
}
*/

Monster::Monster(SDL_Renderer * RendererToUse, int XPosition, int YPosition, std::string FileName, bool UsesTransparency)
{
}
// Standard Destructor:
Monster::~Monster()
{
	delete this;
}
