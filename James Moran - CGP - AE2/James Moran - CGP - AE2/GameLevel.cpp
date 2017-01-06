#include "GameLevel.h"

// Initilisation:
GameLevel::GameLevel(SDL_Renderer* RendererToUse, Vector2D NewBlockDimensions, 
	Vector2D NewLevelDimensions, Vector2D NewScreenDimensions)
{
	LevelRenderer = RendererToUse;
	// For the level's dimensions:
	BlockDimensions = Vector2D(NewBlockDimensions);
	LevelDimensions = Vector2D(NewLevelDimensions);

	GameScreenDimensions = Vector2D(NewScreenDimensions);

	// The grid reference for the Render method to use:
	// (50-50 x 20-20):
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWWWWWW");
	LevelGrid.push_back((std::string)"W..E...E...E.......W"); // (50)
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
	LevelGrid.push_back((std::string)"W...E.....E....E.WWW"); // (800)
	LevelGrid.push_back((std::string)"W..WWWWWWWWWWWWWWWWW");
	LevelGrid.push_back((std::string)"WW.................W");
	LevelGrid.push_back((std::string)"WWWWWWWWWWWWWWWWWWWW");

	// For initialisation of mobile GameEntities:
	std::vector<ValidStartEndXPositionsPerRow> ValidMobileEntityMovementValues = GetValidXPositionsPerRow();


	// Game Entities:
	FirstEnemy = new Enemy(RendererToUse, Vector2D(800, 800), 150, 800, BlockDimensions, 
		NewScreenDimensions, EI_LOWEST_ENEMY, ValidMobileEntityMovementValues);
	SecondEnemy = new Enemy(RendererToUse, Vector2D(100, 50), 600, 50, BlockDimensions, 
		NewScreenDimensions, EI_HIGHEST_ENEMY, ValidMobileEntityMovementValues);
	PlayerCharacter = new Player(RendererToUse, 900, 900, BlockDimensions, 
		NewScreenDimensions, ValidMobileEntityMovementValues);
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

	for each (GameEntity* CurrentDoorEntity in EnemyDoorEntities)
	{
		delete CurrentDoorEntity;
		CurrentDoorEntity = nullptr;
	}
}

// For getting the bounds of the level:
// (-1, a)
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

	if (!BlankBlockTexture)
	{
		InitialiseBlankBlockTexture();
	}
	
	// A less-than or equal to operator was the solution to unintended patterns occuring earlier, as opposed to a less-than operator
	// (for the InnerCounter):
	for (int OuterCounter = 0; OuterCounter < GetHeight(); OuterCounter++)
	{
		for (int InnerCounter = 0; InnerCounter <= GetWidth(); InnerCounter++)
		{
			switch (LevelGrid[OuterCounter][InnerCounter])
			{

			case 'W': // Wall
				RectangleOrigin = DrawBlock(RectangleOrigin, &BlockTextureDimensions, BT_WALL);
				break;

			case 'E': // Enemy Door
				RectangleOrigin = DrawBlock(RectangleOrigin, &BlockTextureDimensions, BT_ENEMY_DOOR);
				break;

			default: // Default to a blank block:
				RectangleOrigin = DrawBlock(RectangleOrigin, &BlockTextureDimensions, BT_BLANK);
				break;

			}
		}

		RectangleOrigin.YComponent += BlockDimensions.YComponent;
		BlockTextureDimensions.y = RectangleOrigin.YComponent;
	}

	// For every Enemy Door:
	GameCollisionSystem::GetCollisionSystem(LevelDimensions.YComponent).CopyEnemyDoorEntities(EnemyDoorEntities);

	// Add mobile-game entities to the end of this collection (after the tiles):
	GameCollisionSystem::GetCollisionSystem(LevelDimensions.YComponent).AddGameEntityToCollection(FirstEnemy);
	GameCollisionSystem::GetCollisionSystem(LevelDimensions.YComponent).AddGameEntityToCollection(SecondEnemy);
	GameCollisionSystem::GetCollisionSystem(LevelDimensions.YComponent).AddGameEntityToCollection(PlayerCharacter);
}

// For updating:
void GameLevel::UpdateLevelState()
{
	// The mobile-entities first:
	FirstEnemy->UpdateEnemy();
	SecondEnemy->UpdateEnemy();
	PlayerCharacter->UpdateEntity();

	/** 
		Then re-draw any doors, after an Enemy
		or the Player has moved over them: 
	*/
	for each (GameEntity* CurrentEnemyDoor in EnemyDoorEntities)
	{
		CurrentEnemyDoor->UpdateEntity();
	}
}

// Check if the tile at PixelCoordinates is a wall:
/*
bool GameLevel::IsWall(Vector2D* PixelCoordinates)
{
	// Get the grid coordinates from PixelCoordinates:
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
*/
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

	// For actually creating the texture:
	SDL_FillRect(BlankBlockSurface, NULL, BlankBlockColour);
	BlankBlockTexture = SDL_CreateTextureFromSurface(LevelRenderer, BlankBlockSurface);
	SDL_FreeSurface(BlankBlockSurface);
}

void GameLevel::AddEntityToCollisionSystem(GameEntity* EntityToAdd)
{
	GameCollisionSystem::GetCollisionSystem(LevelDimensions.YComponent).AddGameEntityToCollection(EntityToAdd);
}

Vector2D GameLevel::DrawBlock(Vector2D CurrentRectanglePosition, SDL_Rect* BlockTextureDimensions, BlockType TypeOfBlock)
{
	Vector2D UpdatedRectanglePosition = CurrentRectanglePosition;
	GameEntity* ThisBlankBlock;
	GameEntity* ThisWallBlock;
	GameEntity* ThisEnemyDoor;

	switch (TypeOfBlock)
	{
	case BT_BLANK:
		ThisBlankBlock = new GameEntity(LevelRenderer, UpdatedRectanglePosition.XComponent,
			UpdatedRectanglePosition.YComponent, "Bitmaps/BlankBlockBitmap.bmp", BlockDimensions,
			GameScreenDimensions, EI_BLANK_BLOCK, GetValidXPositionsPerRow());
		ThisBlankBlock->UpdateEntity();
		AddEntityToCollisionSystem(ThisBlankBlock);
		break;
	
	case BT_WALL:
		ThisWallBlock = new GameEntity(LevelRenderer, UpdatedRectanglePosition.XComponent,
			UpdatedRectanglePosition.YComponent, "Bitmaps/WallBlockBitmap.bmp", BlockDimensions, 
			GameScreenDimensions, EI_WALL_BLOCK, GetValidXPositionsPerRow());
		ThisWallBlock->UpdateEntity();
		AddEntityToCollisionSystem(ThisWallBlock);
		break;

	case BT_ENEMY_DOOR:
		ThisEnemyDoor = new GameEntity(LevelRenderer, UpdatedRectanglePosition.XComponent,
			UpdatedRectanglePosition.YComponent, "Bitmaps/EnemyDoorBitmap.bmp", BlockDimensions,
			GameScreenDimensions, EI_ENEMY_DOOR, GetValidXPositionsPerRow());
		ThisEnemyDoor->UpdateEntity();
		AddEntityToCollisionSystem(ThisEnemyDoor);

		/** 
			Also add this to EnemyDoorEntities, for redrawing if 
			the Player or an Enemy moves over the space it occupies:
		*/
		EnemyDoorEntities.push_back(ThisEnemyDoor);
		break;

	default:
		break;
	}

	// Update the Dimension Rectangle's position:
	UpdateRectangleGridPosition(UpdatedRectanglePosition);
	BlockTextureDimensions->x = UpdatedRectanglePosition.XComponent;

	return UpdatedRectanglePosition;
}

void GameLevel::UpdateRectangleGridPosition(Vector2D& PositionToUpdate)
{
	if ((PositionToUpdate.XComponent) != (BlockDimensions.XComponent * LevelDimensions.XComponent))
	{
		// So long as the width of the level is not equal to the block width^2:
		PositionToUpdate.XComponent += BlockDimensions.XComponent;
	}
	else
	{
		PositionToUpdate.XComponent = 0;
	}	
}

std::vector<ValidStartEndXPositionsPerRow> GameLevel::GetValidXPositionsPerRow()
{
	// Determine the area that is valid for the Player to move into:

	// The valid XPosition for each row:
	std::vector<ValidStartEndXPositionsPerRow> ValidPositions;

	for (int RowCounter = 0; RowCounter < GetHeight(); RowCounter++)
	{
		for (int ColumnCounter = 0; ColumnCounter <= GetWidth(); ColumnCounter++)
		{
			switch (LevelGrid[RowCounter][ColumnCounter])
			{

			case '.':
			case 'E': // Enemy Doors or Blank Spaces are valid for the Player to move in:
				// For the starting point of valid positions for this row:
				if (ValidPositions.size() < RowCounter + 1)
				{
					// For both beginning and end, initially:
					Vector2D InitialValidValues = Vector2D(ColumnCounter * BlockDimensions.XComponent,
						ColumnCounter * BlockDimensions.XComponent);

					ValidPositions.push_back(ValidStartEndXPositionsPerRow(InitialValidValues));
				}
				// Then keep moving along the row till the end is reached:
				else
				{
					ValidPositions[RowCounter].StartEndPositions.YComponent += BlockDimensions.XComponent;
				}
				break;

			default: // Blank for now
				break;

			}
		}
	}

	return ValidPositions;
}

