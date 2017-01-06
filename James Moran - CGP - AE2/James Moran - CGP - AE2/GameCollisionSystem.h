#pragma once

#include "GameEntity.h"
#include <vector>

// Foward declared-classes:
// (Hmm...)
class GameEntity;
class Enemy;

// As well as structures:
struct Vector2D;

// Enumerations:

/**
To determine what direction an Entity is moving
in. This is to handle what corners to check for and
against when checking Entity-space-occupance.
*/

#ifndef ENTITY_MOVEMENT_DIRECTION
#define ENTITY_MOVEMENT_DIRECTION
enum EntityMovementDirection
{
	ED_LEFTWARDS,
	ED_RIGHTWARDS,
	ED_UPWARDS
};
#endif

/** 
	For handling collisions between
	game entities.

	This is a 'static' class, given its use in many places:
*/
class GameCollisionSystem
{

private:

	// Functions:

	/** Standard constructor */
	GameCollisionSystem();

	/** Standard destructor */
	~GameCollisionSystem();

	// Sub-checks involved in an overal collision check:

	/**
		Description: Check if a GameEntity already extends out to the area between
		and including; the ProposedNewTopLeftCorner and ProposedNewTopRightCorner.

		@Params: GameEntity* MovingEntity: The GameEntity that is attemepting to move,
		so as to not return true when checking gets to MovingEntity.
		Vector2D ProposedNewPoint1: Check from this point, to the...
		Vector2D ProposedNewBottomLeftCorner: ...second point, for the Entity trying to translate
		these two points, of their bounding-box (for their new position).
		EntityDirection Movementdirection: The direction MovingEntity is moving in.

		@Return: True if this is the case.
	*/
	bool AnotherGameEntityOccupiesRangeBetweenPoints(GameEntity* MovingEntity, Vector2D ProposedNewPoint1, Vector2D ProposedNewPoint2, 
		EntityMovementDirection MovementDirection);

	/** 
		Description: Check if there is a blocking-GameEntity
		at PositionToCheck.

		@Params: int RowToCheck: The row to check:
		
		Vector2D StartingVertex: The position to check from
		
		Vector2D EndingVertex: The position to check to.

		@Return: bool PositionOccupied: True if there is a
		blocking GameEntity here.	
	*/
	bool GameEntityIsAtPosition(GameEntity* EntityAttemeptingMovement, int RowToCheck, Vector2D StartingVertex, Vector2D EndingVertex, 
		EntityMovementDirection MovementDirection);

	/**
		Description: Get the row number EntityMoving is on.

		@Param: GameEntity* EntityMoving: The Entity to get the
		row number of.

		@Return: int RowNumber: The respective calculated value.
	*/
	int GetEntityRowNumber(GameEntity* EntityMoving);

	/**
		Description: Get the column number EntityMoving is on.

		@Param: GameEntity* EntityMoving: The Entity to get the
		column number of.

		@Return: int ColumnNumber: The respective calculated value.
	*/
	int GetEntityColumnNumber(GameEntity* EntityMoving);

	// Properties:
	
	/** For the rows of all game entities */
	std::vector<std::vector<GameEntity*>> GameEntities;

	/** Temporary storage for each row, before adding the row to GameEntities */
	std::vector<GameEntity*> TemporaryRow;

	/** For all Enemy Doors */
	std::vector<GameEntity*> EnemyDoorEntities;

	/** The maximum number of game-entities per row... */
	int GameEntitiesPerRow;

	/** ...as well as in a column */
	int GameEntitiesPerColumn;

	// Constant values:

	/** 
		An Enemy can only go to another corridor when they
		are at least this close to an Enemy Door
	*/
	const int MAXIMUM_ENEMY_TO_ENEMY_DOOR_PROXIMITY = 5;

	// For reference to the game's dimensions for each block
	const Vector2D BLOCK_DIMENSIONS = Vector2D(50, 50);

public:

	// Functions:

	// Delete the copy constructor and assignment operator:
	GameCollisionSystem(GameCollisionSystem const&) = delete;
	void operator=(GameCollisionSystem const&) = delete;

	/** 
		Description: Add a GameEntity to the collection, for future reference
		in collision checks.

		@Param: GameEntity* EntityToAdd: The respective GameEntity to add
		to the GameEntities collection.
	*/
	void AddGameEntityToCollection(GameEntity* EntityToAdd);

	/**
		Description: Get a static reference to this class.

		@Return: GameCollisionSystem&: The class reference,
		in order to use it. 
	*/
	static GameCollisionSystem& GetCollisionSystem(int NewEntitiesPerRow)
	{
		/**
			(Comments on the respective lines are apparently the case,
             according to 'Loki Astari's' answer: 
			 http://stackoverflow.com/questions/1008019/c-singleton-design-pattern)
		*/
		static GameCollisionSystem Instance; // 'Guaranteed to be destroyed.'
		
		// For setting up the vector of vectors: 
		Instance.GameEntitiesPerRow = NewEntitiesPerRow;

		return Instance; // 'Instantiated on first use.'
	}

	/** 
		Description: Attempt horizontal (leftwards or rightwards) 
		and vertical (upwards or downwards) movement (respectively).

		@Params: std::vector<ValidStartEndXPositionsPerRow> ValidPositionRanges:
		For the positions that are valid for this mobile-entity to
		move into.

		Vector2D ProposedTargetPosition: The intended location to move this
		mobile-entity to.

		@Return: bool MovementValid: For whether movement to the intended 
		position is valid.
	*/
	bool AttemptHorizontalMovement(std::vector<ValidStartEndXPositionsPerRow> 
		ValidPositionRanges, Vector2D ProposedTargetPosition);
	bool AttemptVerticalMovement(std::vector<ValidStartEndXPositionsPerRow>
		ValidPositionRanges, Vector2D ProposedTargetPosition);

	/**
		Description: For GameLevel to copy EnemyDoorEntities
		across to this singleton class (for all instances to use)

		@Param: std::vector<EnemyDoor*> CurrentEnemyDoors:
		The value to parse to this singleton class, for
		EnemyDoorEntities.
	*/
	void CopyEnemyDoorEntities(std::vector<GameEntity*> CurrentEnemyDoors);

	/**
		Description: Check if Enemy is close enough to a door, in order to enter it.

		@Param(s): Vector2D CurrentEnemyPosition: This Enemy's current position
		(in pixel coordinates).

		@Return: bool EnemyIsNearADoor: If true; the enemy will patrol along
		the corridor this door leads to.
	*/
	bool IsEnemyNearAnEnemyDoor(Enemy* ThisEnemyCharacter);

	/**
		The 3 functions below, are for
		checking leftwards, rightwards and
		upwards collision, respectivly.
	*/

	/**
		Description: Allow leftwards movement if there is no collision with
		other game-entities.

		@Params: int ProposedNewNegativeXPosition: The proposed new value of the
		Entity's X-Position (less-than the current value; as
		this bitmap is moving leftwards),
		to check for validility. 

		GameEntity* ConsideredEntity: The GameEntity that is attempting
		to move leftwards.

		@Return: True if movement in the respective direction is possible.
	*/
	bool CheckLeftSideCollision(GameEntity* ConsideredEntity);

	/**
		Description: Allow rightwards movement if there is no collision with
		other game-entities.

		@Params: int ProposedNewPositiveXPosition: The proposed new value of the
		Entity's X-Position (greater-than the current value; as
		this bitmap is moving rightwards),
		to check for validility.

		GameEntity* ConsideredEntity: The GameEntity that is attempting
		to move rightwards.

		@Return: True if movement in the respective direction is possible.
	*/
	bool CheckRightSideCollision(GameEntity* ConsideredEntity);

	/**
		Description: Allow upwards movement if there is no collision with
		other game-entities.

		@Params: int ProposedNewPositiveYPosition: The proposed new value of the
		Entity's Y-Position (greater-than the current value; as
		this bitmap is moving upwards),
		to check for validility. 

		GameEntity* ConsideredEntity: The GameEntity that is attempting
		to move upwards.

		@Return: True if movement in the respective direction is possible.
	*/
	bool CheckTopSideCollision(GameEntity* ConsideredEntity);
};

