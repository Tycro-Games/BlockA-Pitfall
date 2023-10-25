#include "precomp.h"
#include "Coin.h"

Coin::~Coin()
{
	delete subject;
	delete saveLoad;
	delete sprite;
	sprite = nullptr;
}

Coin::Coin()
{
	subject = new Subject();
	saveLoad = new SavingLoading("");
}

void Coin::Render(Surface* screen)
{
	if (!onScreen || !IsActive())
		return;
	const float2 camPos = Camera::GetPosition();
	const int x = static_cast<int>(position.x - camPos.x);
	const int y = static_cast<int>(position.y - camPos.y);

	sprite->Draw(screen, x, y);
}

void Coin::Update(float deltaTime)
{
	deltaTime;
	if (IsActive())
		onScreen = Camera::OnScreen(position, coll);
}

void Coin::Init(const float2& pos)
{
	SetActive(true);
	coll = Box{-DISTANCE_TO_PLAYER, DISTANCE_TO_PLAYER};
	position = pos;
	if (sprite == nullptr)
	{
		sprite = new Sprite(new Surface("assets/coin1_16x16.png"), FRAMES);
	}
	//load save
	saveLoad->SetName(saveName);
	saveLoad->EntryPosition(position);
	uint8_t i = 0;
	saveLoad->LoadData(i);
	if (i)
	{
		SetActive(false);
	}
}

bool Coin::GetOnScreen() const
{
	return onScreen;
}

const float2& Coin::GetPosition() const
{
	return position;
}

void Coin::Collect()
{
	coinSound.play();
	SetActive(false);
	subject->Notify(points, COIN_COLLECTED);
	uint8_t i = 1;
	saveLoad->SaveData(i);
}

Subject* Coin::GetSubject() const
{
	return subject;
}
