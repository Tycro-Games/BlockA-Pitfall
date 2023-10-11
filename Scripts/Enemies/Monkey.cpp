#include "precomp.h"
#include "Monkey.h"


void Monkey::Render(Surface* screen)
{
	if (ball != nullptr)
	{
		ball->Render(screen);
	}
	if (!onScreen)
		return;
	GetDrawCoordinatesMoving();
	screen->Box(x1, y1, x2, y2, PINK);
	GetDrawCoordinatesMoving(GetThrowCollider());
	screen->Box(x1, y1, x2, y2, BLUE);

}

Box Monkey::GetThrowCollider() const
{
	Box b = throwCollider;
	const float sign = headingRight ? -1.0f : 1.0f;
	b.min.x *= sign;
	b.max.x *= sign;
	if (static_cast<int>(sign) == -1)
		swap(b.min.x, b.max.x);
	return b;
}
bool Monkey::SeesPlayer() const
{
	const float2 playerPos = avatar->GetPos();
	const Box playerCol = AABB::At(playerPos, *avatar->GetCollisionChecker()->GetBoxCollider());
	const Box monkeyCollider = AABB::At(position, GetThrowCollider());
	if (AABB::BoxCollides(playerCol, monkeyCollider))
	{
		return true;
	}
	return false;
}

Monkey::~Monkey()
{
	delete ballTimer;
	delete throwTimer;
	delete hitTimer;
	delete colCheck;
	delete currentState;
	delete subject;
}
void Monkey::Update(float deltaTime)
{
	onScreen = Camera::OnScreen(position, col);
	Enemy::Update(deltaTime);
	MonkeyState* state = currentState->Update(this, deltaTime);
	if (ball != nullptr && ballTimer->elapsedF() > TIME_ALIVE_BALL) {
		delete ball;
		ball = nullptr;
	}
	if (ball != nullptr)
	{
		ball->Update(deltaTime);
	}
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
	throwTimer = new Timer();
	ballTimer = new Timer();
	headingRight = true;

	//collision checker is also used in avatar
	colCheck = new CollisionChecker(&position, floors, ladders);
	throwCollider = Box{ minThrow,maxhrow };
	currentState = new MonkeyToGroundState();
}

float Monkey::GetValueFromMonkeyFunction(float t, bool positive)

{
	const float value = -(4 * powf(t - 1, 7)
		- cosf(8 * t + 9)) * 0.1f;
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

Timer* Monkey::GetThrowTimer() const
{
	return throwTimer;
}

Timer* Monkey::GetBallTimer() const
{
	return ballTimer;
}

void Monkey::SetHeading(bool _heading)
{
	headingRight = _heading;
}

bool Monkey::GetHeading() const
{
	return headingRight;
}

void Monkey::SetBall(MonkeyBall* _ball)
{

	ball = _ball;
}
MonkeyBall* Monkey::GetBall()
{

	return ball;
}

