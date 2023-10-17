#pragma once

class Score : public Observer
{
public:
	Score();
	~Score() override;
	virtual void Render(Surface* screen) = 0;
	void AddPoints(uint points);
	void Reset();
	void SetPoints(uint startPoints);
	uint GetScore() const;
	void SetPosition(const float2& _pos);
	const char* GetScoreWithZeros(int& n, int& x, int& y) const;
	const char* GetScore(int& n, int& x, int& y) const;

protected:
	float2 pos;
	uint score = 0;
	const uint8_t digits = 8;
};
