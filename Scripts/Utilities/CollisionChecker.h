#pragma once

struct Box;
class Zipline;
class Tilemap;
class Rope;

class CollisionChecker
{
public:
	CollisionChecker(float2* pos, Tilemap* floors, Tilemap* ladders, Zipline* ziplines, size_t ziplineCount,
		Rope* ropes, size_t rope_count);
	~CollisionChecker();
	bool IsCollidingLadders(const Box* col, float2& floorPos) const;
	bool IsCollidingLadders(const float2& newPos, const Box* col, float2& floorPos) const;
	bool IsCollidingLadders(const float2& newPos, const Box* col) const;
	bool IsCollidingLadders(const Box* col) const;
	bool IsCollidingFloors(const float2& newPos, const Box* col) const;
	bool IsCollidingFloors(const Box* col) const;
	bool IsCollidingFloors(const Box* col, float2& floorPos) const;
	bool IsCollidingRopes(float2*& pMovingPart) const;
	bool IsCollidingZiplines(float2& _normal, float2& _start, float2& _end) const;


	Tilemap* GetFloors() const;
	Tilemap* GetLadders() const;
	Rope* GetRopes() const;
	Zipline* GetZiplines() const;
	size_t GetZiplinesCount() const;
	size_t GetRopeCount() const;
	const Box* GetFloorCollider() const;

	const Box* GetBoxCollider() const;

	const Box* GetJumpCollider() const;
	float2 GetFloorPos() const;
	float2 GetJumpPos() const;
	float2 GetBoxColliderPos() const;
	float2 GetBoxColliderOffset() const;

private:

	float2* pos;
	Tilemap* floors;
	Tilemap* ladders;
	Zipline* ziplines;
	size_t ziplineCount;

	Rope* ropes;
	size_t ropeCount ;

	//ziplines and ropes
	const float RADIUS_TO_ZIPLINE = 25.0f;
	const float RADIUS_TO_ROPE = 30.0f;
	const float ZIPLINE_OFFSET_END = 25.0f;
	const float ZIPLINE_OFFSET_START = 25.0f;

	//colliders
	const float BOX_SIZE = 5.0f;
	const float2 BOX_POS = { 9.0f, 17.0f };
	Box* boxCollider;

	const float FLOOR_SIZE = 8.0f;
	Box* floorCollider;
	const float2 FLOOR_POS = { 9.5f,30.0f };

	Box* jumpCollider;
	const float2 JUMP_POS = { 9.5f, 42.0f };
	const float JUMP_SIZE_X = 8.0f;
	const float JUMP_SIZE_Y = 4.0f;
};
