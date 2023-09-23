#include "precomp.h"
#include "State.h"


void State::SetVariables(Avatar& p, float deltaTime, float2& pos, float2& newPos, Tilemap*& floors, Camera*& cam,
	Box& floorCollider, Box& boxCollider, float2& velocity)
{
	pos = p.GetPos();
	floors = p.GetFloors();
	cam = p.GetCamera();
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	velocity = p.GetVelocity();
}
