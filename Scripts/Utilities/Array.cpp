#include "precomp.h"
#include "Array.h"



template <class T>
Array<T>::~Array()
{
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

//template <>
//void Array<Rock*>::Print()
//{
//	for (uint i=0;i<count;i++)
//	{
//		cout << cell[i]->GetPosition() << ' ';
//	}
//	cout << endl;
//}

template <class T>
T& Array<T>::operator[](const size_t index)
{
	return cell[index];
}

template <class T>
T& Array<T>::Get(size_t index)
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
template class Array<Rock*>;