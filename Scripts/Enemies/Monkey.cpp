#include "precomp.h"
#include "Monkey.h"

#include "EnemyStates/MonkeyToGroundState.h"

void Monkey::Render(Surface* screen)
{
	if (!onScreen)
		return;
	GetDrawCoordinatesMoving();
	screen->Box(x1, y1, x2, y2, PINK);
}

Monkey::~Monkey()
{
	delete colCheck;
	delete currentState;
}
void Monkey::Update(float deltaTime)
{
	onScreen = Camera::OnScreen(position, col);
	MonkeyState* state = currentState->Update(this, deltaTime);
	if (state != nullptr)
	{
		delete currentState;
		currentState = state;
	}
}

float Monkey::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}

void Monkey::Init(const float2& pos, Tilemap* floors, Tilemap* ladders, Avatar& p)
{
	position = pos;
	avatar = &p;
	col = Box{ -DISTANCE_TO_PLAYER,DISTANCE_TO_PLAYER };
	SetDamage(DAMAGE);
	//collision checker is also used in avatar
	colCheck = new CollisionChecker(&position, floors, ladders);
	currentState = new MonkeyToGroundState();
}

float Monkey::GetValueFromMonkeyFunction(float t)
{
	return -(4 * powf(t - 1, 7) - cosf(8 * t + 9)) * 0.1f;
}

CollisionChecker* Monkey::GetCollisionChecker() const
{
	return colCheck;
}

