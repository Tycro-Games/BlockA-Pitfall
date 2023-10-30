#pragma once
class Enemy;
constexpr uint MAX_ENEMIES_NUMBER = 100;

class WinCondition : public Observer
{
public:
	WinCondition();
	~WinCondition() override;
	void Notify(int context, EVENT ev) override;
	void AddEnemy(Enemy& enemy);
	bool AnyEnemiesLeft() const;

	Subject* GetSubject() const;

private:
	//original static array
	//Enemy* enemies[MAX_ENEMIES_NUMBER];
	DynamicArray<Enemy*> enemies;

	Subject* subject = nullptr;

	uint indexEnemies = 0;
};
