#include "precomp.h"
#include "State.h"


void State::SetVariables(Avatar& p)
{
	pos = p.pGetPos();
	velocity = p.pGetVelocity();

	floors = p.GetFloors();
	cam = p.GetCamera();
	floorCollider = p.GetFloorCollider();
	boxCollider = p.GetBoxCollider();
	speed = p.GetSpeed();
}
