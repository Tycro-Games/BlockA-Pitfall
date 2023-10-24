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
	const int x = static_cast<int>(position.x - camPos.x);
	const int y = static_cast<int>(position.y - camPos.y);

	sprite->Draw(screen, x, y);
#ifdef _DEBUG
	Box a = AABB::At({position.x, position.y}, coll);
	screen->Box(
		static_cast<int>(a.min.x),
		static_cast<int>(a.min.y),
		static_cast<int>(a.max.x),
		static_cast<int>(a.max.y),
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

	GetJSONString();
	float test = 0;
	saveLoad->LoadData(test);
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

void Checkpoint::GetJSONString()
{
	char name[50] = {};
	strcat(name, saveName);
	const int offset = sprintf(name + strlen(saveName), " %f", position.x);
	sprintf(name + strlen(saveName) + offset, " %f", position.y);
	saveLoad->SetName(name);
}

void Checkpoint::SaveToJSON()
{
	//used as a flag that this should be inactive
	saveLoad->SaveData(position.x);
	subject->Notify(0, SAVE_CHECKPOINT);
}

void Checkpoint::Deactivate()
{
	activated = true;

	sprite->SetFrame(1);
}

void Checkpoint::Activate()
{
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
