#include "precomp.h"
#include "PlayerScore.h"

PlayerScore::PlayerScore()
{
	SetPosition(POSITION);
}

void PlayerScore::Notify(int context, EVENT ev)
{
	switch (ev)
	{
	case ENEMY_DEAD:
		AddPoints(static_cast<uint>(context));
		break;
	default:
		break;
	}
}

void PlayerScore::Render(Surface* screen)
{
	int n, x, y;
	const char* c = GetScoreWithZeros(n, x, y);
	if (n > 0)
		screen->Print(c, x, y, WHITE);
	delete[]c;
}
