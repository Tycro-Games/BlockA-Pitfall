#pragma once

class PlayerScore : public Score
{
public:
	PlayerScore();
	~PlayerScore() override;
	void Notify(int context, EVENT ev) override;
	void Render(Surface* screen) override;

private:
	const float2 POSITION = {100, 50};
	const uint8_t SCORE_DIGITS = 8;

	const int POINTS_FOR_COINS = 225;

	SavingLoading* saveLoad = nullptr;
	const char* saveName = "PlayerScore:";
};
