#pragma once
#include "Array.h"

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
	bool IsCollidingFloorsComplete(const float2& newPos, const Box* col) const;
	bool IsCollidingFloors(const Box* col) const;
	bool IsCollidingFloors(const Box* col, float2& floorPos) const;
	bool IsCollidingRopes(float2*& pMovingPart) const;
	bool IsCollidingZiplines(float2& _normal, float2& _start, float2& _end) const;
	void SetRopesZiplines(Array<Zipline>& _ziplines, Array<Rope>& _ropes);



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

	Array<Zipline>* ziplines;
	Array<Rope>* ropes;

	//ziplines and ropes
	const float RADIUS_TO_ZIPLINE = 25.0f;
	const float RADIUS_TO_ROPE = 30.0f;
	const float ZIPLINE_OFFSET_END = 25.0f;
	const float ZIPLINE_OFFSET_START = 25.0f;
	//Adriaensen, Remi (231390),  explained how to fix warning C4324 on discord

	//colliders
	const float2 FLOOR_POS = { 9.5f,30.0f };
	const float2 JUMP_POS = { 9.5f, 42.0f };
	const float2 BOX_POS = { 9.0f, 17.0f };
	Box* floorCollider;
	Box* jumpCollider;
	Box* boxCollider;

	const float BOX_SIZE = 5.0f;
	const float FLOOR_SIZE = 8.0f;

	const float JUMP_SIZE_X = 8.0f;
	const float JUMP_SIZE_Y = 4.0f;
};
