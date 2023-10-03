#pragma once

class Health
{
public:
	void TakeDamage(const int dg)
	{
		hp -= dg;
	}
	bool IsDead() const
	{
		return hp <= 0;
	}
	int GetHp()const;
private:
	int hp = 100;
};
