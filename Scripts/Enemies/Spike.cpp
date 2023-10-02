#include "precomp.h"
#include "Spike.h"

void Spike::Init(const float2& _position)
{
	position = _position;
	cout << "Spike spawned at:" << position << '\n';
}
