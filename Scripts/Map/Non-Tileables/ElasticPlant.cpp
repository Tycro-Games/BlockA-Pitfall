#include "precomp.h"
#include "ElasticPlant.h"

ElasticPlant::~ElasticPlant()
{
}

void ElasticPlant::Render(Surface* screen)
{
	if (!onScreen)
		return;
	const float2 camPos = Camera::GetPosition();
	const int x1 = static_cast<int>(position.x - camPos.x + coll.min.x);
	const int y1 = static_cast<int>(position.y - camPos.y + coll.min.y);
	const float xL = firstPosition.x - camPos.x;
	const float yL = firstPosition.y - camPos.y;
	const float xL2 = position.x - camPos.x;
	const float yL2 = position.y - camPos.y;

	const int x2 = static_cast<int>(position.x - camPos.x + coll.max.x);
	const int y2 = static_cast<int>(position.y - camPos.y + coll.max.y);
	screen->Line(xL, yL,
		xL2, yL2, GREEN);

	if (activate)
		screen->Box(x1, y1, x2, y2, ORANGE);
	else
	{
		screen->Box(x1, y1, x2, y2, GREEN);

	}

}

float ElasticPlant::GetElasticPlantFunction(float _elapsed) const
{
	return sinf(_elapsed) * AMP;
}
float ElasticPlant::GetPercentOfSpeed() const
{
	return clamp(0.0f, 1.0f, invlerp(-AMP, 0.0f, sinf(elapsed) * AMP));
}

void ElasticPlant::Update(float deltaTime)
{
	onScreen = Camera::OnScreen(position, coll);
	if (onScreen && activate)
	{
		elapsed += deltaTime * SPEED;
		const float y = GetElasticPlantFunction(elapsed);
		position.y += y;
		if (position.y < firstPosition.y)
			position.y = firstPosition.y;
	}
}

void ElasticPlant::Init(const float2& _position)
{
	position = _position;
	firstPosition = position;
	coll = Box{ -DISTANCE_TO_PLAYER, DISTANCE_TO_PLAYER };
}

bool ElasticPlant::GetOnScreen() const
{
	return onScreen;

}

float2* ElasticPlant::pGetPosition()
{
	return &position;
}

void ElasticPlant::SetActivation(bool _activate)
{
	elapsed = 0;
	activate = _activate;
	if (!activate)//default position
	{
		position = firstPosition;
	}
}
