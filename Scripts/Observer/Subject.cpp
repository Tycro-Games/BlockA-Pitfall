#include "precomp.h"
#include "Subject.h"

void Subject::AddObserver(Observer& obs)
{
	//add observers to the array
	observers[index++] = &obs;
}

void Subject::RemoveObserver(Observer& obs)
{
	for (uint i = 0; i < index; i++)
	{
		if (observers[i] == &obs)
		{
			for (uint j = i; j < index; j++)
			{
				observers[j] = observers[j + 1];
			}
		}
	}
	index--;
}

void Subject::Notify(int ctx, EVENT ev) const
{
	for (uint i = 0; i < index; i++)
	{
		observers[i]->Notify(ctx, ev);
	}
}
