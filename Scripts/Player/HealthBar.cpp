#include "precomp.h"
#include "HealthBar.h"

HealthBar::~HealthBar()
{
	delete sprite;
	delete t;
	delete deathSubject;
	delete hp;
}

void HealthBar::Init(const char* spritePath)
{
	sprite = new Sprite(new Surface(spritePath), NUMBER_OF_FRAMES);
	deathSubject = new Subject();
	hp = new Health();
	t = new Timer();

	UpdateUI();
}

void HealthBar::Render(Surface* screen) const
{
	sprite->SetFrame(currentframe);
	sprite->Draw(screen, xPos, yPos);
}


void HealthBar::UpdateUI()
{
	if (hp->IsDead())
	{
		currentframe = NUMBER_OF_FRAMES - 1;
		deathSubject->Notify(0, PLAYER_DEAD);
		cout << "player dead'\n";
	}
	else
	{
		//gets the correct frame based on the remaining health
		currentframe = static_cast<int>(static_cast<float>(maxHealth - hp->GetHp()) / 10.0f);
	}
}

void HealthBar::Notify(int context, EVENT ev)
{
	switch (ev)
	{
	case PLAYER_HIT:
		if (t->elapsed() > HIT_COOLDOWN)
		{
			hp->TakeDamage(context);
			cout << "takes damage'\n";
			UpdateUI();
			t->reset();
		}
		break;
	default:
		break;
	}
}

Subject* HealthBar::GetSubject() const
{
	return deathSubject;
}
