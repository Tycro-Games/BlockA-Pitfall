#pragma once

class PlayerScore : public Score
{
public:
	PlayerScore();
	~PlayerScore() override = default;
	void Notify(int context, EVENT ev) override;
	void Render(Surface* screen) override;
private:
	const float2 POSITION= { 100, 50 };
};
