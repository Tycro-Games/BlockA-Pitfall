#pragma once

class ElasticPlant : public Entity
{
public:
	~ElasticPlant() override;
	void Render(Surface* screen) override;
	float GetElasticPlantFunction(float _elapsed) const;
	float GetPercentOfSpeed() const;
	void Update(float deltaTime) override;
	void Init(const float2& _position);
	bool GetOnScreen() const;
	float2* pGetPosition();
	void SetActivation(bool _activate);

private:
	float2 position = 0;
	float2 firstPosition = 0;
	bool activate = false;
	float elapsed = 0;
	bool onScreen = false;
	const float DISTANCE_TO_PLAYER = 10.0f;
	Box coll;
	const float SPEED = 4.0f;
	const float AMP = 4.0f;
};
