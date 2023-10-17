#include "precomp.h"
#include "CoinScore.h"

CoinScore::~CoinScore()
{
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
	const char* c = GetScore(n, x, y);
	if (n > 0)
		screen->Print(c, x, y, WHITE);
	delete[] c;

}
