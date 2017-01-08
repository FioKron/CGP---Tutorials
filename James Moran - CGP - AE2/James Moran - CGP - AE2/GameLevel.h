#pragma once

#include "Enemy.h"
#include "Player.h"
#include "GameBitmap.h"
#include "GameCollisionSystem.h"
#include <vector>

// Forward declared classes again (argh):
class Player;
class Enemy;

// For mapping out collision:
#ifndef VALID_START_END_POSITIONS
#define VALID_START_END_POSITIONS
struct ValidStartEndPositions
{
	/** 
		The X-Component is the start position
		and the Y-Component is the end position
	*/
	Vector2D StartEndPositions;

	ValidStartEndPositions(Vector2D NewStartEnd)
	{
		StartEndPositions = NewStartEnd;
	}
};

#endif 


class GameLevel
{
	// To refer to each type of block:
	enum BlockType
	{
		BT_BLANK,
		BT_WALL,
		BT_DOOR,
		BT_ENEMY_DOOR,
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

	// Tile Checking:

	//bool IsWall(Vector2D* PixelCoordinates);

	// Get methods:

	/** 
		To get the Player Character reference this class holds
		(for the InputManager to use).
	*/
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

	std::vector<std::string> LevelGrid;

	/** Notable Game Entities on the level */
	Enemy* FirstEnemy;
	Enemy* SecondEnemy;
	Player* PlayerCharacter;
	/** For all Enemy Doors */
	std::vector<GameEntity*> EnemyDoorEntities;

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

	/** 
		Description: Get the valid points for movement (by the Player and 
		any Enemies), for each row (when moving leftwards or rightwards).

		@Return: std::vector<ValidStartEndPosition> ValidPositions:
		For any Entity's valid movement positions within the rows of the
		game level.
	*/
	std::vector<ValidStartEndPositions> GetValidXPositionsPerRow();

	/**
		Description: Get the valid points for movement (by the Player and
		any Enemies), for each Column (when moving upwards or downwards).

		@Return: std::vector<ValidStartEndPosition> ValidPositions:
		For any Entity's valid movement position ranges,
		within the columns of the game level.
	*/
	std::vector<std::vector<ValidStartEndPositions>> GetValidYPositionsPerColumn();

	/**
		Description: Update ValidPositions (from the function above).

		@Params: std::vector<ValidStartEndPositions> ValidColumnPositions:
		The current state of valid positions, within a column, the Player can
		move into.

		char PreviousBlockType: The type of block identified within this row of 
		the column, during the last call to this function.

		int ColumnCounter, int RowCounter: From the inner and outer for loops;
		for use in identifying the current position in this column, as well
		as for calculations.

		@Return: std::vector<std::vector<ValidStartEndPositions>> ValidColumnPositions:
		The valid point ranges within a column, the Player can move into.
	*/
	std::vector<std::vector<ValidStartEndPositions>> 
		UpdateValidColumnPositions(std::vector<std::vector<ValidStartEndPositions>> ValidColumnPositions,
		char CurrentBlockType, char PreviousBlockType, int ColumnCounter, int RowCounter);
};

