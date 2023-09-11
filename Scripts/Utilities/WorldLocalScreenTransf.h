#pragma once

class WorldLocalScreenTransf
{
public:
	//it receives it as a screen position
	static void Init(float2 screenPos);
	//get into object space from https://github.com/OneBogdan01/MathLibrary/blob/822e5a2a8234bee520e32008b3ae56be2e01b735/Transform.cpp
	//assumes canonical world origin
	static float2 ConvertScreenToWorldSpace(float2 pos);
	static float2 ConvertWorldSpaceToScreen(float2 pos);
	
	static float2 Convert(float2 pos);

private:
	//assumes center of the screen
	static float2 origin;
};
