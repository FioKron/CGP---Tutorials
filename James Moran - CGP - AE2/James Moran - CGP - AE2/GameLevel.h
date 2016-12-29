#pragma once

#include "Enemy.h"
#include "Player.h"
#include "GameBitmap.h"
#include "GameCollisionSystem.h"
#include <vector>

class GameLevel
{
	// To refer to each type of block (significant types of block only though):
	enum BlockType
	{
		BlankBlock,
		WallBlock,
		DoorBlock,
		KeyBlock
	};

public:

	// Functions:

	GameLevel(SDL_Renderer* RendererToUse, Vector2D NewBlockDimensions, Vector2D NewLevelDimensions);
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

		@Param: GameEntity* BlockToAdd: The block to add to the collision system's
		GameEntities collection.
	*/
	void AddBlockToCollisionSystem(GameEntity* BlockToAdd);

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

