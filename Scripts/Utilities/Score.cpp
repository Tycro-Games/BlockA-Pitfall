#include "precomp.h"
#include "Score.h"

Score::Score()
{
	score = 0;
	//might need to add some loading from file for saved scores
}

Score::~Score()
{
}

void Score::AddPoints(uint points)
{
	score += points;
}

void Score::Reset()
{
}

void Score::SetPoints(uint startPoints)
{
	score = startPoints;
}

uint Score::GetScore() const
{
	return score;
}


void Score::SetPosition(const float2& _pos)
{
	pos = _pos;
}

const char* Score::GetScoreWithZeros(int& n, int& x, int& y, const uint8_t digits) const
{
	x = static_cast<int>(pos.x);
	y = static_cast<int>(pos.y);
	char* c = new char[digits + 1];
	n = sprintf(c, "%d", score);
	int index = 0;
	if (n < digits)
	{
		char* addZero = new char[digits + 1];
		for (int i = 0; i < digits - n; i++)
		{
			addZero[i] = '0';
		}
		for (int i = digits - n; i < digits; i++)
		{
			addZero[i] = c[index++];
		}
		addZero[digits] = '\0';
		strcpy(c, addZero);
		delete[] addZero;
	}
	return c;
}
