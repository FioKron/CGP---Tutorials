#include "GameLevel.h"

// Initilisation:
GameLevel::GameLevel(SDL_Renderer* RendererToUse, Vector2D NewBlockDimensions, Vector2D NewLevelDimensions)
{
	LevelRenderer = RendererToUse;
	// For the level's dimensions:
	BlockDimensions = Vector2D(NewBlockDimensions);
	LevelDimensions = Vector2D(NewLevelDimensions);

	// Game Entities:
	FirstEnemy = new Enemy(RendererToUse, Vector2D(800, 800), 150, 800);
	SecondEnemy = new Enemy(RendererToUse, Vector2D(100, 50), 600, 50);
	PlayerCharacter = new Player(RendererToUse, 900, 900);

	// The grid reference for the Render method to use:
	// (50-50 x 20-20):
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWWWWWW");
	LevelGrid.push_back((std::string)"W..................W"); // (50)
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWW......W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWW.....W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWW....W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWW...W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWWW..W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWW....WW");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWW....WWW");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWW...WWWW");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWW..WWWWW");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWW.....W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWW....W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWW...W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWWW..W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWW..WW");
	LevelGrid.push_back((std::string)"W................WWW"); // (800)
	LevelGrid.push_back((std::string)"W..WWWWWWWWWWWWWWWWW");
	LevelGrid.push_back((std::string)"WW.................W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWWWWWW");
}

// Clean-up:
GameLevel::~GameLevel()
{
	for (int Counter = 0; Counter < LevelGrid.size(); Counter++)
	{
		LevelGrid[Counter] = "";
	}

	if (PlayerCharacter)
	{
		delete PlayerCharacter;
		PlayerCharacter = nullptr;
	}

	if (SecondEnemy)
	{
		delete SecondEnemy;
		SecondEnemy = nullptr;
	}

	if (FirstEnemy)
	{
		delete FirstEnemy;
		FirstEnemy = nullptr;
	}	
}

// For getting the bounds of the level:
int GameLevel::GetHeight()
{
	return LevelDimensions.YComponent;
}

int GameLevel::GetWidth()
{
	return LevelDimensions.XComponent;
}

// Show the level to the Player:
void GameLevel::Render()
{
	/**/
	// For rendering all the blocks, of each row:
	Vector2D RectangleOrigin = Vector2D(0, 0);
	SDL_Rect BlockTextureDimensions = { RectangleOrigin.XComponent, RectangleOrigin.YComponent, BlockDimensions.XComponent, BlockDimensions.YComponent };

	// Initialise textures:
	if (!WallBlockTexture)
	{
		InitialiseWallBlockTexture();
	}
	
	if (!BlankBlockTexture)
	{
		InitialiseBlankBlockTexture();
	}
	
	// A less-than or equal to operator was the solution to unintended patterns occuring earlier, as opposed to a less-than operator:
	for (int OuterCounter = 0; OuterCounter <= GetHeight(); OuterCounter++)
	{
		for (int InnerCounter = 0; InnerCounter <= GetWidth(); InnerCounter++)
		{
			if (LevelGrid[OuterCounter][InnerCounter] == 'W')
			{
				RectangleOrigin = DrawBlock(RectangleOrigin, &BlockTextureDimensions, "Wall");				
			}
			else
			{
				RectangleOrigin = DrawBlock(RectangleOrigin, &BlockTextureDimensions, "Blank");
			}
		}

		RectangleOrigin.YComponent += BlockDimensions.YComponent;
		BlockTextureDimensions.y = RectangleOrigin.YComponent;
	}
}

// For updating:
void GameLevel::UpdateLevelState()
{
	FirstEnemy->UpdateEntity();
	SecondEnemy->UpdateEntity();
	PlayerCharacter->UpdateEntity();
}

/**
	Is it a bird? Is it a plane? Is it a wall?
	Well I'm not sure about if 'it' is a bird or plane,
	but I can check if 'it' is a wall...
*/
bool GameLevel::IsWall(Vector2D* PixelCoordinates)
{
	// Yes, a constant value is used for here testing,
	// resolve this if the test is succesful:
	int XPosition = (PixelCoordinates->XComponent / BlockDimensions.XComponent) - 1;
	int YPosition = (PixelCoordinates->YComponent / BlockDimensions.YComponent) - 1;

	if (LevelGrid[YPosition][XPosition] == 'W')
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Get methods here:

Player* GameLevel::GetPlayerCharacterReference()
{
	if (PlayerCharacter)
	{
		return PlayerCharacter;
	}
}

/**
	Texture initialisation:
*/

void GameLevel::InitialiseBlankBlockTexture()
{
	SDL_Surface* BlankBlockSurface = SDL_CreateRGBSurface(0, BlockDimensions.XComponent, BlockDimensions.YComponent, 32, 0, 0, 0, 0);

	// White for a blank space:
	Uint32 BlankBlockColour = SDL_MapRGB(BlankBlockSurface->format, 255, 255, 255);

	SDL_FillRect(BlankBlockSurface, NULL, BlankBlockColour);
	BlankBlockTexture = SDL_CreateTextureFromSurface(LevelRenderer, BlankBlockSurface);
	SDL_FreeSurface(BlankBlockSurface);
}

void GameLevel::InitialiseWallBlockTexture()
{
	SDL_Surface* BlockSurface = SDL_CreateRGBSurface(0, BlockDimensions.XComponent, BlockDimensions.YComponent, 32, 0, 0, 0, 0);

	// Orange for a Wall block:
	Uint32 WallBlockColour = SDL_MapRGB(BlockSurface->format, 255, 128, 0);
	
	SDL_FillRect(BlockSurface, NULL, WallBlockColour);
	WallBlockTexture = SDL_CreateTextureFromSurface(LevelRenderer, BlockSurface);	
	SDL_FreeSurface(BlockSurface);
}

Vector2D GameLevel::DrawBlock(Vector2D CurrentRectanglePosition, SDL_Rect* BlockTextureDimensions, std::string BlockType)
{
	Vector2D UpdatedRectanglePosition = CurrentRectanglePosition;

	if (BlockType == "Wall")
	{
		SDL_RenderCopy(LevelRenderer, WallBlockTexture, NULL, BlockTextureDimensions);
	}
	else if (BlockType == "Blank")
	{
		SDL_RenderCopy(LevelRenderer, BlankBlockTexture, NULL, BlockTextureDimensions);
	}

	// Update the Dimension Rectangle's position:
	if ((UpdatedRectanglePosition.XComponent) != (BlockDimensions.XComponent * LevelDimensions.XComponent))
	{
		// So long as the width of the level is not equal to the block width^2:
		UpdatedRectanglePosition.XComponent += BlockDimensions.XComponent;
	}
	else
	{
		UpdatedRectanglePosition.XComponent = 0;
	}

	BlockTextureDimensions->x = UpdatedRectanglePosition.XComponent;

	return UpdatedRectanglePosition;
}

