#include "precomp.h"
#include "WorldLocalScreenTransf.h"


//solves linker errors
float2 WorldLocalScreenTransf::origin;
void WorldLocalScreenTransf::Init(float2 screenPos)
{
	origin = screenPos;
}

float2 WorldLocalScreenTransf::ConvertScreenToWorldSpace(float2 pos)
{

	return pos - origin;
}
float2 WorldLocalScreenTransf::ConvertWorldSpaceToScreen(float2 pos)
{

	return pos + origin;
}


