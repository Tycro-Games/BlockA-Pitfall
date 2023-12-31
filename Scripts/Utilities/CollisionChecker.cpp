﻿#include "precomp.h"
#include "CollisionChecker.h"


const Box* CollisionChecker::GetFloorCollider() const
{
	return floorCollider;
}

const Box* CollisionChecker::GetBoxCollider() const
{
	return boxCollider;
}

const Box* CollisionChecker::GetJumpCollider() const
{
	return jumpCollider;
}

float2 CollisionChecker::GetFloorPos() const
{
	return FLOOR_POS;
}

float2 CollisionChecker::GetJumpPos() const
{
	return JUMP_POS;
}

float2 CollisionChecker::GetBoxColliderPos() const
{
	return *pos + BOX_POS;
}

float2 CollisionChecker::GetBoxColliderOffset() const
{
	return BOX_POS;
}

CollisionChecker::CollisionChecker(float2* pos, Tilemap* floors, Tilemap* ladders) : pos(pos),
	floors(floors),
	ladders(ladders), ziplines(nullptr), ropes(nullptr), elasticPlants(nullptr)
{
	floorCollider = new Box{FLOOR_POS - FLOOR_SIZE, FLOOR_POS + FLOOR_SIZE};
	boxCollider = new Box{BOX_POS - BOX_SIZE, BOX_POS + BOX_SIZE};
	jumpCollider = new Box{JUMP_POS - float2{JUMP_SIZE_X, JUMP_SIZE_Y}, JUMP_POS + float2{JUMP_SIZE_X, JUMP_SIZE_Y}};
}

CollisionChecker::~CollisionChecker()
{
	delete floorCollider;
	delete boxCollider;
	delete jumpCollider;
}

bool CollisionChecker::IsCollidingLadders(const Box* col, float2& floorPos) const
{
	return ladders->IsCollidingBox(*pos, *col, floorPos);
}

bool CollisionChecker::IsCollidingLadders(const float2& newPos, const Box* col) const
{
	return ladders->IsCollidingBox(newPos, *col);
}

bool CollisionChecker::IsCollidingLadders(const Box* col) const
{
	return ladders->IsCollidingBox(*pos, *col);
}

bool CollisionChecker::IsCollidingFloors(const float2& newPos, const Box* col) const
{
	return floors->IsCollidingBox(newPos, *col);
}

bool CollisionChecker::IsInGameBounds(const float2& newPos, const Box* col) const
{
	return floors->IsInsideGameBounds(newPos, *col);
}

bool CollisionChecker::IsCollidingFloorsAllCorners(const float2& newPos, const Box* col) const
{
	return floors->IsCollidingBoxComplete(newPos, *col);
}

bool CollisionChecker::IsCollidingFloors(const Box* col) const
{
	return floors->IsCollidingBox(*pos, *col);
}

bool CollisionChecker::IsCollidingFloors(const Box* col, float2& floorPos) const
{
	return floors->IsCollidingBox(*pos, *col, floorPos);
}

bool CollisionChecker::IsCollidingRopes(float2*& pMovingPart) const
{
	for (uint i = 0; i < ropes->Size(); i++)
	{
		if ((*ropes)[i].GetOnScreen())
		{
			float2 toPlayer = (*pos + BOX_POS) - (*ropes)[i].GetMovingPart();
			if (sqrLength(toPlayer) <= RADIUS_TO_ROPE * RADIUS_TO_ROPE)
			{
				pMovingPart = (*ropes)[i].pGetMovingPart();
				return true;
			}
		}
	}
	return false;
}

bool CollisionChecker::IsCollidingElasticPlant(ElasticPlant*& pElasticPlant) const
{
	for (uint i = 0; i < elasticPlants->Size(); i++)
	{
		if ((*elasticPlants)[i].GetOnScreen())
		{
			//converts local to world space

			//this is circle collision
			float2 elasticPoint = *(*elasticPlants)[i].pGetPosition();
			float2 toPlayer = (*pos + BOX_POS) - elasticPoint;
			/*if (length(toPlayer) <= RADIUS_TO_ROPE)
			{
				pElasticPlant = &(*elasticPlants)[i];
				return true;
			}*/
			//more efficient, no sqrt
			if (sqrLength(toPlayer) <= RADIUS_TO_ELASTIC * RADIUS_TO_ELASTIC)
			{
				pElasticPlant = &(*elasticPlants)[i];
				return true;
			}
		}
	}
	return false;
}

void CollisionChecker::IsCollidingCoins() const
{
	for (uint i = 0; i < coins->Size(); i++)
	{
		if ((*coins)[i].GetOnScreen() && (*coins)[i].IsActive())
		{
			const float2 toPlayer = (*pos + BOX_POS) - (*coins)[i].GetPosition();
			if (length(toPlayer) <= RADIUS_TO_COIN)
			{
				(*coins)[i].Collect();
			}
		}
	}
}

void CollisionChecker::IsCollidingCheckpoints() const
{
	for (uint i = 0; i < checkpoints->Size(); i++)
	{
		if (!(*checkpoints)[i].IsActivated() && (*checkpoints)[i].GetOnScreen() && (*checkpoints)[i].IsActive())
		{
			const float2 toPlayer = (*pos + BOX_POS) - (*checkpoints)[i].GetPosition();
			if (length(toPlayer) <= RADIUS_TO_COIN)
			{
				(*checkpoints)[i].Activate();
			}
		}
	}
}

bool CollisionChecker::IsCollidingZiplines(float2& _normal,
                                           float2& _start,
                                           float2& _end) const
{
	for (uint i = 0; i < ziplines->Size(); i++)
		if ((*ziplines)[i].GetOnScreen())
		{
			float2 start = 0;
			float2 end = 0;
			(*ziplines)[i].GetStartEnd(start, end);

			float2 a = end - start;
			float2 toPlayer = -(start - (*pos + BOX_POS));
			float2 toPlayerP = normalize(a) * clamp(length(toPlayer),
			                                        ZIPLINE_OFFSET_START,
			                                        length(a) - ZIPLINE_OFFSET_END); //not after the end or start
			float2 normal = toPlayer - toPlayerP;
			if (length(normal) <= RADIUS_TO_ZIPLINE)
			{
				_normal = normal;
				_start = start;
				_end = end;
				return true;
			}
		}
	return false;
}

void CollisionChecker::SetNonTiles(StaticArray<Zipline>& _ziplines, StaticArray<Rope>& _ropes,
                                   StaticArray<ElasticPlant>& _elasticPlants,
                                   StaticArray<Coin>& _coins, StaticArray<Checkpoint>& _checkpoints)
{
	ziplines = &_ziplines;

	ropes = &_ropes;
	elasticPlants = &_elasticPlants;
	coins = &_coins;
	checkpoints = &_checkpoints;
}
