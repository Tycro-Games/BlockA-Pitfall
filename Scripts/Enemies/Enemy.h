#pragma once

class Enemy
{
public:
	virtual ~Enemy()=default;
	virtual void Update(float deltaTime) = 0;
	Subject* GetSubject() const;
	float2 GetPosition()const;
protected:
	float2 position = 0;

	Subject* subject = nullptr;
	Avatar* avatar = nullptr;
};
