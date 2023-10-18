#pragma once


struct Timer;
class Health;

class HealthBar : public Observer
{
public:
	~HealthBar() override;
	void Init(const char* spritePath);
	void Render(Surface* screen) const;
	void UpdateUI();
	void Notify(int context, EVENT ev) override;
	Subject* GetSubject() const;

private:
	Timer* t = nullptr;
	const float HIT_COOLDOWN = 0.5f;
	Health* hp = nullptr;
	Sprite* sprite = nullptr;
	const int NUMBER_OF_FRAMES = 11;
	Subject* deathSubject = nullptr;
	int currentframe = 0;
	const int maxHealth = 100;
	const int xPos = 920;
	const int yPos = 50;
};
