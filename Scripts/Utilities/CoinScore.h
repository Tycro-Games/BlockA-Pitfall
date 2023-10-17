#pragma once

class CoinScore : public Score
{
public:
	~CoinScore() override;
	void Notify(int context, EVENT ev) override;
	void Render(Surface* screen) override;

private:
};
