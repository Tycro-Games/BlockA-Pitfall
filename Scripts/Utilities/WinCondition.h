#pragma once
class Enemy;
constexpr uint MAX_ENEMIES_NUMBER = 100;

class WinCondition : public Observer
{
public:
	WinCondition();
	~WinCondition() override;
	void Notify(int context, EVENT ev) override;
	void AddEnemy(Enemy* enemy);
	bool AnyEnemiesLeft() const;

	Subject* GetSubject() const;

private:
	Enemy* enemies[MAX_ENEMIES_NUMBER] = {};
	uint indexEnemies = 0;
	Subject* subject = nullptr;
};
