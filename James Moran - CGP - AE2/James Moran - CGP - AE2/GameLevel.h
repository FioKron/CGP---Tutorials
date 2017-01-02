#pragma once

#include "Enemy.h"
#include "Player.h"
#include "GameBitmap.h"
#include "GameCollisionSystem.h"
#include <vector>

// Forward declared classes again (argh):
class Player;
class Enemy;

class GameLevel
{
	// To refer to each type of block:
	enum BlockType
	{
		BT_BLANK,
		BT_WALL,
		BT_DOOR,
		BT_KEY
	};

public:

	// Functions:

	/** Standard constructor: */
	GameLevel(SDL_Renderer* RendererToUse, Vector2D NewBlockDimensions, 
		Vector2D NewLevelDimensions, Vector2D NewScreenDimensions);
	
	/** Standard destructor: */
	~GameLevel();
	
	/** For retriving the bounds of the level */
	int GetHeight();
	int GetWidth();

	/** Rendering handle */
	void Render();

	/** For updating */
	void UpdateLevelState();

	// For showing blocks:
	//void ShowWallBlock();
	//void ShowBlankSpace();

	// Tile Checking:

	bool IsWall(Vector2D* PixelCoordinates);

	// Get methods:

	/** To get the Player Character reference this class holds */
	Player* GetPlayerCharacterReference();

private:

	// Properties:

	/** Rendering components */
	SDL_Texture* WallBlockTexture;
	SDL_Texture* BlankBlockTexture;
	SDL_Renderer* LevelRenderer;

	/** Game Level components */
	Vector2D BlockDimensions;
	Vector2D LevelDimensions;

	Vector2D GameScreenDimensions;

	//Vector2D* LevelDimensions;
	std::vector<std::string> LevelGrid;

	/** Game Entities on the level */
	Enemy* FirstEnemy;
	Enemy* SecondEnemy;
	Player* PlayerCharacter;

	// Functions:

	// For setting up the blank block texture:
	void InitialiseBlankBlockTexture();

	/**
		Add a specific type of block to the GameCollisionSystem's collection:

		@Param: GameEntity* EntityToAdd: The Entity (Block, Player etc.)
		to add to the collision system's GameEntities collection.
	*/
	void AddEntityToCollisionSystem(GameEntity* EntityToAdd);

	// For showing blocks of various types

	/**
		Place a block on the current row .

		@Params: Vector2D CurrentRectanglePosition: To update in this
		function, to move the origin across the row for each block.

		SDL_Rect* BlockTextureDimensions: The rendering target.

		BlockType TypeOfBlock: The type of block to display at the current location.

		@Return: Vector2D UpdatedRectanglePosition: The new values of
		the parameter parsed in to start off with.
	*/
	Vector2D DrawBlock(Vector2D CurrentRectanglePosition, SDL_Rect* BlockTextureDimensions, BlockType TypeOfBlock);

	/** 
		Description: Update the position of the rectangle on the grid, 
		whilst rendering the level.

		@Param: Vector2D& PositionToUpdate: The Vector2D to modify as appropriate.

		@Return: Vector2D PositionToUpdate: After receiving the appropirate 
		updating.
	*/
	void UpdateRectangleGridPosition(Vector2D& PositionToUpdate);
};

