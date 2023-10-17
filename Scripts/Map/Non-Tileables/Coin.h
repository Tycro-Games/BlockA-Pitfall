#pragma once


class Coin : public Entity
{
public:
	~Coin() override;
	void Render(Surface* screen) override;
	void Update(float deltaTime) override;
	void Init(const float2& pos);
	bool GetOnScreen() const;
	const float2& GetPosition() const;
	void Collect();
	Subject* GetSubject() const;
private:
	Subject* subject = nullptr;
	float2 position = 0;
	//we only need one coin sprite for all of them
	inline static Sprite* sprite = nullptr;
	Box coll;
	bool onScreen = false;
	const int FRAMES = 15;
	const float DISTANCE_TO_PLAYER = 16.0f;
	const int points = 100;
};
