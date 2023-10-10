#pragma once

class ElasticPlantState :public PlayerState
{
public:
	void OnEnter(Avatar& _p) override;
	PlayerState* Update(float deltaTime) override;
	void OnExit() override;
	void pSetPlant(ElasticPlant* _plant);

private:
	ElasticPlant* plant=nullptr;
	float2* elasticPoint = 0;
	/*const float2 OFFSET_ROPE = { 7.0f,10.0f };*/
	float2 previousR = 0;
	const float MAX_THRESHOLD = 0.7f;
	const float MAX_JUMP = 4.0f;
};


