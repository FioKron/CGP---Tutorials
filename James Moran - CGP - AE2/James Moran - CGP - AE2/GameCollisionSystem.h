#pragma once

#include "GameEntity.h"
#include <vector>

// Foward declared-classes:
// (Hmm...)
class GameEntity;

// As well as structures:
struct Vector2D;

// Enumerations:

/** 
	To determine what direction an Entity is moving 
	in. This is to handle what corners to check for and 
	against when checking Entity-space-occupance.
*/
enum EntityDirection
{
	Leftwards,
	Rightwards,
	Upwards
};

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
	bool AnotherGameEntityOccupiesRangeBetweenPoints(GameEntity* MovingEntity, Vector2D ProposedNewPoint1, Vector2D ProposedNewPoint2, EntityDirection MovementDirection);

	// Properties:

	std::vector<GameEntity*> GameEntities;

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
	static GameCollisionSystem& GetCollisionSystem()
	{
		/**
			(Comments on the respective lines are apparently the case,
             according to 'Loki Astari's' answer: 
			 http://stackoverflow.com/questions/1008019/c-singleton-design-pattern)
		*/
		static GameCollisionSystem Instance; // 'Guaranteed to be destroyed.'

		return Instance; // 'Instantiated on first use.'
	}

	/**
		The 3 functions below, are for
		checking leftwards, rightwards and
		upwards collision, respectivly.
	*/

	/**
		@Params: int ProposedNewNegativeX: The proposed new value of the
		Entity's X-Position (less-than the current value; as
		this bitmap is moving leftwards),
		to check for validility. 

		GameEntity* ConsideredEntity: The GameEntity that is attempting
		to move leftwards.

		@Return: True if movement in the respective direction is possible.
	*/
	bool CheckLeftSideCollision(GameEntity* ConsideredEntity, int ProposedNewNegativeX);

	/**
		@Params: int ProposedNewPositiveX: The proposed new value of the
		Entity's X-Position (greater-than the current value; as
		this bitmap is moving rightwards),
		to check for validility.

		GameEntity* ConsideredEntity: The GameEntity that is attempting
		to move rightwards.

		@Return: True if movement in the respective direction is possible.
	*/
	bool CheckRightSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveX);

	/**
		@Params: int ProposedNewPositiveY: The proposed new value of the
		Entity's Y-Position (greater-than the current value; as
		this bitmap is moving upwards),
		to check for validility. 

		GameEntity* ConsideredEntity: The GameEntity that is attempting
		to move upwards.

		@Return: True if movement in the respective direction is possible.
	*/
	bool CheckTopSideCollision(GameEntity* ConsideredEntity, int ProposedNewPositiveY);
};

