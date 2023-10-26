#include "precomp.h"
#include "Boar.h"

void Boar::Render(Surface* screen)
{
	if (!onScreen)
		return;
	GetDrawCoordinatesMoving();
#ifdef _DEBUG
	screen->Box(x1, y1, x2, y2, GREEN);
#endif

	boarSurface_->GetSurface()->Clear(0);
	if (headingRight)
	{
		preRendered->DrawFlippedX(boarSurface_->GetSurface(), 0, 0);
	}
	else
	{
		preRendered->Draw(boarSurface_->GetSurface(), 0, 0);
	}

	boarSurface_->Draw(screen, x1, y1);
}

void Boar::Update(float deltaTime)
{
	onScreen = Camera::OnScreen(position, col);

	Enemy::Update(deltaTime);

	BoarState* state = currentState->Update(this, deltaTime);
	if (state != nullptr)
	{
		currentState->OnExit();
		delete currentState;
		currentState = state;
		currentState->OnEnter();
	}
}

Boar::~Boar()
{
	delete hitRecently;
	delete currentState;
	delete boarSprite;
	delete preRendered;
	delete boarSurface_;
}

Boar::Boar()
{
	hitRecently = new Timer();

	boarSprite = new Sprite(new Surface("assets/monkey.png"), FRAMES);

	Surface* surf = new Surface(RESIZE, RESIZE);
	surf->Clear(0xf00);
	preRendered = new Sprite(surf, 1);
	surf->Clear(0);

	Surface* surfR = new Surface(RESIZE, RESIZE);
	surfR->Clear(0xf00);
	boarSurface_ = new Sprite(surfR, 1);
	surfR->Clear(0);

	boarSprite->DrawScaled(0, 0, RESIZE, RESIZE, preRendered->GetSurface());
	surface = boarSurface_->GetSurface();
}

bool Boar::AtackPlayer()
{
	return TryToHitPlayer(DISTANCE_TO_PLAYER);
}

void Boar::Init(const float2& _a, const float2& _b, Avatar& _avatar)
{
	SetActive(true);
	delete currentState;
	currentState = new BoarPatrolState();
	currentState->OnEnter();

	avatar = &_avatar;
	pointA = _a;
	pointB = _b;

	position = pointA;
	desiredPos = pointB;
	col = Box{-DISTANCE_TO_PLAYER, DISTANCE_TO_PLAYER};
	SetHP(HP);
	SetPoints(BOAR_POINTS);
	SetDamage(DAMAGE);
	//load save
	saveLoad->SetName(saveName);
	saveLoad->EntryPosition(position);
	uint8_t i = 0;
	saveLoad->LoadData(i);
	if (i)
	{
		SetActive(false);
	}
	headingRight = false;
}

const float2& Boar::GetDesiredPos() const
{
	return desiredPos;
}

const float2& Boar::GetStartPos() const
{
	return pointA;
}

const float2& Boar::GetEndPos() const
{
	return pointB;
}

void Boar::SwitchPositions()
{
	headingRight = !headingRight;
	swap(pointA, pointB);
}

void Boar::SetDesiredPos(const float2& _desiredPos)
{
	desiredPos = _desiredPos;
}

float Boar::GetDistanceToPlayer()
{
	return DISTANCE_TO_PLAYER;
}


Timer* Boar::GetHitTimer() const
{
	return hitRecently;
}

void Boar::Dead()
{
	Enemy::Dead();
	uint8_t i = 1;
	saveLoad->SaveData(i);
}
