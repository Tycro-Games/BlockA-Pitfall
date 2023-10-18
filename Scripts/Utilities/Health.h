#pragma once

class Health
{
public:
	//doing this makes two constructors with different parameters
	Health(int _hp = 100);

	void TakeDamage(const int dg)
	{
		hp -= dg;
	}

	bool IsDead() const
	{
		return hp <= 0;
	}

	int GetHp() const;
	void SetHp(int _hp);

private:
	int hp;
};
