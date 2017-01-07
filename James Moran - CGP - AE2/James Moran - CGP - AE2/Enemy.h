#pragma once
#include "GameEntity.h"
#include <vector>

// Forward references again (welp):
class GameEntity;

struct ValidStartEndPositions;

/** 
	This struct contains both a reference to an EnemyDoor,
	as well as a flag for if this Enemy is close enough to
	enter the door

	RESOLVE ISSUES WITH THIS STRUCT DFAWDFAW

#ifndef ENEMY_DOOR_AND_PROXIMITY_FLAG
#define ENEMY_DOOR_AND_PROXIMITY_FLAG
struct DoorReferenceAndProximityDetectionFlag
{
	EnemyDoor* DoorReference;
	bool ProximityFlag;

	DoorReferenceAndProximityDetectionFlag(EnemyDoor* NewReference, bool NewProximityFlag)
	{
		DoorReference = NewReference;
		ProximityFlag = NewProximityFlag;
	}

	DoorReferenceAndProximityDetectionFlag()
	{

	}
};
#endif 
*/
class Enemy : public GameEntity
{
	
private:

	// Properties:

	/** For the route the Enemy is to take for patrolling */
	Vector2D PatrolStartPoint;
	Vector2D PatrolEndPoint;

	/** 
		This door is parsed by reference into
		IsEnemyNearAnEnemyDoor(), to update this door appropriatly
	*/
	//EnemyDoor* ReferenceDoor;

	/** 
		An ad-hoc timer (for allowing the 
		Enemy to return to the corridor the Player can see)
	*/
	float TestTimer;

	// Constant values:

	/** 
		The time in milliseconds to wait for, before performing
		the next attempt at movement
	*/
	const Uint32 WAIT_TIME_BETWEEN_MOVEMENT_ATTEMPTS = 10;

	// Flags:

	bool MovingToEndPatrolPoint;
	bool PatrollingAnotherCorridor;

	// Functions:

	// For handling sub-patrol movement behavior:

	void MoveRightwardsToPatrolEndPoint();
	void MoveLeftwardsToPatrolEndPoint();
	void MoveRightwardsToPatrolStartPoint();
	void MoveLeftwardsToPatrolStartPoint();

	/** Invert MovingToEndPatrolPoint */
	void MovingToOtherPatrolPoint();

	/**
		For validation.

		@Param: Vector2D TargetPatrolPoint: The point
		this Enemy is moving towards.
	*/
	void ValidateLeftwardsMovement(Vector2D TargetPatrolPoint);
	void ValidateRightwardsMovement(Vector2D TargetPatrolPoint);

	/** Handle moving between points on the patrol */
	void MoveToPatrolEndPoint();
	void MoveToPatrolStartPoint();
	void DeterminePointToMoveTo();

	// Handling general movment
	void MoveLeftwards();
	void MoveRightWards();

	/** 
		Description: For waiting after translation (movement).

		@Param: Uint32 MilliSeconds: To parse into SDL_Delay(),
		to have the game wait for that many milliseconds.
	*/
	void WaitAfterTranslation(Uint32 MilliSeconds);

public:

	// Functions:

	/** Standard constructor */
	Enemy(SDL_Renderer* RendererToUse, Vector2D NewPatrolEndPoint, int XPosition, int YPosition, Vector2D ActiveBlockDimensions,
		Vector2D NewScreenDimensions, EntityID UniqueID, std::vector<ValidStartEndPositions> NewValidMobileEntityRowMovementValues,
		std::vector<ValidStartEndPositions> NewValidMobileEntityColumnMovementValues,
		std::string FileName = "Bitmaps/EnemyBitmap.bmp", bool UsesTransparency = true);

	/** Update handler */
	void UpdateEnemy();

	// Flag manipulation:
	void NowPatrollingAnotherCorridor();
	void BackToPatrollingThisCorridor();
};

