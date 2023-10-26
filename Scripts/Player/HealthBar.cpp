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
	saveLoad = new SavingLoading("Health:");
	UpdateUI();
}

void HealthBar::Init()
{
	int startingHP = 100;
	saveLoad->LoadData(startingHP);
	hp->SetHp(startingHP);
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
		saveLoad->ResetAllData();

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
			hp->TakeDamage(abs(context));
			int getHp = hp->GetHp();
			saveLoad->SaveData(getHp);
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

void HealthBar::SetStartingHP(int _hp)
{
	hp->SetHp(_hp);
	UpdateUI();
}
