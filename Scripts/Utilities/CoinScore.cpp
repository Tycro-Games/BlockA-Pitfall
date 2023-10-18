#include "precomp.h"
#include "CoinScore.h"

CoinScore::~CoinScore()
{
	delete sprite;
}

void CoinScore::Notify(int context, EVENT ev)
{
	context;
	switch (ev)
	{
	case COIN_COLLECTED:
		AddPoints(1);
	default:
		break;
	}
}

void CoinScore::Render(Surface* screen)
{
	int n, x, y;
	const char* c = GetScoreWithZeros(n, x, y, COINS_DIGITS);
	if (n > 0)
		screen->Print(c, x, y, WHITE);
	sprite->DrawScaled(x - PRE_OFFSET_X, y - sprite->GetHeight(), POST_OFFSET_X_Y, POST_OFFSET_X_Y, screen);
	screen->Print("x", x - OFFSET_X, y, WHITE);

	delete[] c;
}

CoinScore::CoinScore()
{
	SetPosition(POSITION);
	sprite = new Sprite(new Surface("assets/coin1_16x16.png"), FRAMES);
}
