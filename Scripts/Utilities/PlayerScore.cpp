#include "precomp.h"
#include "PlayerScore.h"

PlayerScore::PlayerScore()
{
	SetPosition(POSITION);
	saveLoad = new SavingLoading(saveName);
	Init();
}

PlayerScore::~PlayerScore()
{
	delete saveLoad;
}

void PlayerScore::Notify(int context, EVENT ev)
{
	switch (ev)
	{
	case ENEMY_DEAD:
		AddPoints(static_cast<uint>(context));

		break;
	case COIN_COLLECTED:
		AddPoints(POINTS_FOR_COINS);
		saveLoad->SaveData(score);

		break;
	default:
		break;
	}
}

void PlayerScore::Render(Surface* screen)
{
	int n, x, y;
	const char* c = GetScoreWithZeros(n, x, y, SCORE_DIGITS);
	if (n > 0)
		screen->Print(c, x, y, WHITE);
	delete[]c;
}

void PlayerScore::Init()
{
	score = 0;

	saveLoad->LoadData(score);
}
