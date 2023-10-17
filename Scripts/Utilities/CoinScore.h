#pragma once

class CoinScore : public Score
{
public:
	~CoinScore() override;
	void Notify(int context, EVENT ev) override;
	void Render(Surface* screen) override;
	CoinScore();
private:
	const int FRAMES = 15;
	Sprite* sprite = nullptr;
	const float2 POSITION = float2(1000, 560);
	const int PRE_OFFSET_X = 96;
	const int POST_OFFSET_X_Y = 64;
	const int OFFSET_X = 30;
};
