#include "precomp.h"
#include "Health.h"

Health::Health(int _hp)
{
	hp = _hp;
}

int Health::GetHp() const
{
	return hp;
}

void Health::SetHp(int _hp)
{
	hp = _hp;
}
