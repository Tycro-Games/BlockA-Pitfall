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

protected:
	const char* GetScoreWithZeros(int& n, int& x, int& y, uint8_t digits) const;
	//solved alignment specifier warning

	float2* p;

	float2 pos;
	uint score = 0;
};
