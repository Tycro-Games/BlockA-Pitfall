#include "precomp.h"
#include "WinCondition.h"

WinCondition::WinCondition(): enemies{}
{
	subject = new Subject();
}

WinCondition::~WinCondition()
{
	delete subject;
}

void WinCondition::Notify(int context, EVENT ev)
{
	context;
	switch (ev)
	{
	case ENEMY_DEAD:
		if (!AnyEnemiesLeft())
		{
			//win
			subject->Notify(0, ALL_ENEMIES_DEAD);
		}
		break;
	default:
		break;
	}
}

void WinCondition::AddEnemy(Enemy* enemy)
{
	enemies[indexEnemies++] = enemy;
}

bool WinCondition::AnyEnemiesLeft() const
{
	for (uint i = 0; i < indexEnemies; i++)
	{
		if (enemies[i]->IsActive())
			return true;
	}
	return false;
}

Subject* WinCondition::GetSubject() const
{
	return subject;
}
