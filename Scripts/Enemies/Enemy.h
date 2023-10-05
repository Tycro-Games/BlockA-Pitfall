#pragma once

class Enemy : public Entity
{
public:
	~Enemy() override = default;
	void Update(float deltaTime) override = 0;

	Subject* GetSubject() const;
	const float2& GetPosition()const;
	void TryToHitPlayer(float distanceToPlayer);

	void SetPosition(const float2& pos);
	void SetDamage(uint dg);
	virtual float GetDistanceToPlayer() = 0;
protected:
	void GetDrawCoordinates();
	void GetDrawCoordinatesMoving();

	float2 position = 0;
	uint damage = 0;
	Subject* subject = nullptr;
	Avatar* avatar = nullptr;
	bool onScreen = false;

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	Box col;
};
