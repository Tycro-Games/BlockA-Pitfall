#include "precomp.h"
#include "CoinScore.h"

CoinScore::~CoinScore()
{
}

void CoinScore::Notify(int context, EVENT ev)
{
	switch (ev)
	{
	case COIN_COLLECTED:
		AddPoints(static_cast<uint>(context));
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
