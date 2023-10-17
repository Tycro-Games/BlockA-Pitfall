#include "precomp.h"
#include "Array.h"



template <class T>
Array<T>::~Array()
{
	//how to solve for the pointer to pointer case?
	delete[] cell;
}

template <class T>
void Array<T>::Init(size_t _count)
{
	cell = new T[_count];

	count = _count;
}

template <class T>
size_t Array<T>::GetCount() const
{
	return count;
}

template <class T>
T& Array<T>::operator[](const size_t index)
{
	return cell[index];
}



//from here https://github.com/Tycro-Games/AUSS/blob/master/src/pool.cpp
template class Array<Zipline>;
template class Array<Rope>;
template class Array<Spike>;
template class Array<Monkey>;
template class Array<Boar>;
template class Array<ElasticPlant>;
template class Array<Rock>;
template class Array<Coin>;