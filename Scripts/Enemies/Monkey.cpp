#include "precomp.h"
#include "Monkey.h"

#include "EnemyStates/MonkeyToGroundState.h"

void Monkey::Render(Surface* screen)
{
	if (!onScreen)
		return;
	GetDrawCoordinatesMoving();
	screen->Box(x1, y1, x2, y2, PINK);
	GetDrawCoordinatesMoving(throwCollider);
	screen->Box(x1, y1, x2, y2, BLUE);

}

Monkey::~Monkey()
{
	delete hitTimer;
	delete colCheck;
	delete currentState;
	delete subject;
}
void Monkey::Update(float deltaTime)
{
	onScreen = Camera::OnScreen(position, col);
	MonkeyState* state = currentState->Update(this, deltaTime);
	if (state != nullptr)
	{
		currentState->OnExit();
		delete currentState;
		currentState = state;
		currentState->OnEnter();
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
	subject = new Subject();
	hitTimer = new Timer();
	//collision checker is also used in avatar
	colCheck = new CollisionChecker(&position, floors, ladders);
	throwCollider = Box{ minThrow,maxhrow };
	currentState = new MonkeyToGroundState();
}

float Monkey::GetValueFromMonkeyFunction(float t, bool positive )

{
	float value = -(4 * powf(t - 1, 7) - cosf(8 * t + 9)) * 0.1f;
	if (positive)
		return abs(value);
	//we need negative
	if (value < 0)
	{
		return value;
	}
	return -value;
}

CollisionChecker* Monkey::GetCollisionChecker() const
{
	return colCheck;
}

Timer* Monkey::GetHitTimer() const
{
	return hitTimer;
}

