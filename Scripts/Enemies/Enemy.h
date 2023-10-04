#pragma once

class Enemy : public Entity
{
public:
	~Enemy() override = default;
	void Update(float deltaTime) override = 0;
	Subject* GetSubject() const;
	float2 GetPosition()const;
protected:
	float2 position = 0;

	Subject* subject = nullptr;
	Avatar* avatar = nullptr;
};
