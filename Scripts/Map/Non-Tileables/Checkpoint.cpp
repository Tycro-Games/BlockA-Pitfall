#include "precomp.h"
#include "Checkpoint.h"

Checkpoint::Checkpoint()
{
	saveLoad = new SavingLoading("");
	subject = new Subject();
	sprite = new Sprite(new Surface("assets/Checkpoint.png"), FRAMES);
}

Checkpoint::~Checkpoint()
{
	delete subject;
	delete sprite;
	delete saveLoad;
}

void Checkpoint::Render(Surface* screen)
{
	if (!onScreen)
		return;
	const float2 camPos = Camera::GetPosition();
	const int x = static_cast<int>(position.x + coll.min.x - camPos.x);
	const int y = static_cast<int>(position.y + coll.min.y - camPos.y);

	sprite->Draw(screen, x, y);
#ifdef _DEBUG
	const int dX = static_cast<int>(position.x + coll.max.x - camPos.x);
	const int dY = static_cast<int>(position.y + coll.max.y - camPos.y);
	screen->Box(
		x,
		y,
		dX,
		dY,
		WHITE);
#endif
}

void Checkpoint::Update(float deltaTime)
{
	deltaTime;
	onScreen = Camera::OnScreen(position, coll);
}

void Checkpoint::Init(const float2& pos)
{
	SetActive(true);

	coll = Box{-DISTANCE_TO_PLAYER, DISTANCE_TO_PLAYER};
	activated = false;
	position = pos;

	saveLoad->SetName(saveName);
	saveLoad->EntryPosition(position);
	GetJSONString();
	uint8_t test = 0;
	saveLoad->LoadData(test);
	sprite->SetFrame(0);
	if (test != 0)
	{
		Deactivate();
	}
}

bool Checkpoint::GetOnScreen() const
{
	return onScreen;
}

const float2& Checkpoint::GetPosition() const
{
	return position;
}

void Checkpoint::GetJSONString() const
{
	char name[50] = {};
	strcat(name, saveName);
	const int offset = sprintf(name + strlen(saveName), " %f", position.x);
	sprintf(name + strlen(saveName) + offset, " %f", position.y);
	saveLoad->SetName(name);
}

void Checkpoint::SaveToJSON() const
{
	//used as a flag that this should be inactive
	uint8_t t = 1;
	saveLoad->SaveData(t);
	subject->Notify(0, SAVE_CHECKPOINT);
}

void Checkpoint::Deactivate()
{
	activated = true;

	sprite->SetFrame(1);
}

void Checkpoint::Activate()
{
	checkSound.play();
	SaveToJSON();
	Deactivate();
}

bool Checkpoint::IsActivated() const
{
	return activated;
}

Subject* Checkpoint::GetSubject() const
{
	return subject;
}
