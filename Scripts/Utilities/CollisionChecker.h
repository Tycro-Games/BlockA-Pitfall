﻿#pragma once
#include "StaticArray.h"
#include "Scripts/Map/Non-Tileables/Coin.h"

class Checkpoint;
class ElasticPlant;
struct Box;
class Zipline;
class Tilemap;
class Rope;

class CollisionChecker
{
public:
	CollisionChecker(float2* pos, Tilemap* floors, Tilemap* ladders);
	~CollisionChecker();
	bool IsCollidingLadders(const Box* col, float2& floorPos) const;
	bool IsCollidingLadders(const float2& newPos, const Box* col) const;
	bool IsCollidingLadders(const Box* col) const;
	bool IsCollidingFloors(const float2& newPos, const Box* col) const;
	bool IsInGameBounds(const float2& newPos, const Box* col) const;
	bool IsCollidingFloorsAllCorners(const float2& newPos, const Box* col) const;
	bool IsCollidingFloors(const Box* col) const;
	bool IsCollidingFloors(const Box* col, float2& floorPos) const;
	bool IsCollidingRopes(float2*& pMovingPart) const;
	bool IsCollidingElasticPlant(ElasticPlant*& pElasticPlant) const;
	void IsCollidingCoins() const;
	void IsCollidingCheckpoints() const;
	bool IsCollidingZiplines(float2& _normal, float2& _start, float2& _end) const;
	void SetNonTiles(StaticArray<Zipline>& _ziplines, StaticArray<Rope>& _ropes,
	                 StaticArray<ElasticPlant>& _elasticPlants,
	                 StaticArray<Coin>& _coins, StaticArray<Checkpoint>& _checkpoints);


	const Box* GetFloorCollider() const;

	const Box* GetBoxCollider() const;

	const Box* GetJumpCollider() const;
	float2 GetFloorPos() const;
	float2 GetJumpPos() const;
	float2 GetBoxColliderPos() const;
	float2 GetBoxColliderOffset() const;

private:
	float2* pos = nullptr;
	Tilemap* floors;
	Tilemap* ladders;

	StaticArray<Zipline>* ziplines;
	StaticArray<Rope>* ropes;
	StaticArray<ElasticPlant>* elasticPlants;
	StaticArray<Coin>* coins;
	StaticArray<Checkpoint>* checkpoints;
	//Adriaensen, Remi (231390),  explained how to fix warning C4324 on discord

	//colliders
	//defined relative to player pos
	const float2 FLOOR_POS = {9.5f, 30.0f};
	const float2 JUMP_POS = {9.5f, 42.0f};
	const float2 BOX_POS = {9.0f, 25.0f};
	//ziplines and ropes
	const float RADIUS_TO_ZIPLINE = 25.0f;
	const float RADIUS_TO_ROPE = 50.0f;
	const float RADIUS_TO_ELASTIC = 40.0f;
	const float RADIUS_TO_COIN = 20.0f;
	const float RADIUS_TO_CHECKPOINT = 16.0f;
	const float ZIPLINE_OFFSET_END = 25.0f;
	const float ZIPLINE_OFFSET_START = 25.0f;

	Box* floorCollider;
	Box* jumpCollider;
	Box* boxCollider;

	const float BOX_SIZE = 8.0f;
	const float FLOOR_SIZE = 8.0f;

	const float JUMP_SIZE_X = 8.0f;
	const float JUMP_SIZE_Y = 4.0f;
};
