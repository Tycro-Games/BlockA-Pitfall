#pragma once

class MathLibrary
{
public:
	template <typename  T>
	static T Clamp(T min, T max, T value)
	{
		if (value > max)
			value = max;
		else if (value < min)
			value = min;
		return value;
	}
	template <typename  T>

	static T Min(T a, T b)
	{
		if (a > b)
			return b;
		return a;
	}

	template <typename  T>
	static T Max(T a, T b)
	{
		if (a > b)
			return a;
		return b;
	}

	template <typename T>
	static int Abs(T a)
	{
		if (a < 0)
			return a * -1;
		return a;
	}



};
