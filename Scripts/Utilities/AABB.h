#pragma once

// added source https://studiofreya.com/3d-math-and-physics/simple-aabb-vs-aabb-collision-detection/
struct Box
{
	float2 min{}, max{};
	Box() = default;

	explicit Box(const float2& min, const float2& max) :
		min(min), max(max)
	{
	}
};

//struct Circle
//{
//	float2 c{};
//	float r{};
//	Circle() = default;
//	Circle(const float2 center, const float radius)
//		:c(center), r(radius)
//	{
//
//	}
//};
struct AABB
{
	static bool BoxCollides(const Box& a, const Box& b);
	//static bool CircleCollides(const Circle& a, const Circle& b);
	static Box At(const float2& pos, const Box& b);
	//static Circle At(float2 pos, const Circle& b);
};
