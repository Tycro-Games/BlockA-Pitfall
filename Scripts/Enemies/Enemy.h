#pragma once

class Enemy : public Entity
{
public:
	~Enemy() override;
	Enemy();
	void Update(float deltaTime) override;

	Subject* GetSubject() const;
	const float2& GetPosition() const;
	bool TryToHitPlayer(float distanceToPlayer) const;
	virtual void Dead();
	void HitByPlayer(int _damage);
	void DetectHit();
	void SetPosition(const float2& pos);
	void SetDamage(int dg);
	virtual float GetDistanceToPlayer() = 0;
	Box* GetBox();
	Avatar* GetAvatar() const;
	bool IsOnScreen() const;
	void SetPoints(int p);
	void SetHP(int _hp) const;
	virtual Surface* GetSurface();

protected:
	Surface* surface = nullptr;
	Health* hp = nullptr;
	void GetDrawCoordinates();
	void GetDrawCoordinatesMoving();
	void GetDrawCoordinatesMoving(const Box& col);

	float2 position = 0;
	int damage = 0;
	Subject* subject = nullptr;
	Avatar* avatar = nullptr;
	bool onScreen = false;
	bool dead = false;

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	Box col;

private:
	int points = 10;
};
