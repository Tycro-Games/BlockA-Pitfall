#pragma once
//based on my previos implementation: https://github.com/Tycro-Games/AUSS/blob/master/src/dynamic_array.cpp
template <class T>
class DynamicArray
{
public:
	DynamicArray()
	{
		Resize(4);
	}

	~DynamicArray()
	{
		delete[]arr;
	}


	DynamicArray(size_t size)
	{
		if (size > 16)
		{
			const size_t nextPowerOfTwo = static_cast<size_t>(pow(2, ceil(log2(size))));
			Resize(nextPowerOfTwo);
		}
		else
			Resize(16);
	}

	T& operator[](const size_t index)
	{
		assert(index < maxSize);


		return arr[index];
	}

	const T& operator[](const size_t index) const
	{
		assert(index < maxSize);


		return arr[index];
	}


	void PushBack(const T& item)
	{
		if (count < maxSize)
			arr[count++] = item;
		else
		{
			DoubleSize();
			arr[count++] = item;
		}
	}


	void PushUnique(const T& item)
	{
		//if it already in the array skip it
		if (this->Find(item) != -1)
			return;
		if (count < maxSize)
			arr[count++] = item;
		else
		{
			DoubleSize();

			arr[count++] = item;
		}
	}

	void DoubleSize()
	{
		T* aux = new T[count];
		for (uint i = 0; i < count; i++)
			aux[i] = arr[i];
		delete[]arr;
		Resize(maxSize * 2);
		for (uint i = 0; i < count; i++)
			arr[i] = aux[i];
		delete[]aux;
	}


	void HalfSize()
	{
		T* aux = new T[count];
		for (uint i = 0; i < count; i++)
			aux[i] = arr[i];
		delete[]arr;
		Resize(maxSize / 2);
		for (uint i = 0; i < count; i++)
			arr[i] = aux[i];
		delete[]aux;
	}


	size_t Size() const
	{
		return count;
	}


	void Print()
	{
		if (count > 0)
		{
			for (uint i = 0; i < count; i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << '\n';
		}
	}


	void Print(size_t& i, size_t& j)
	{
		for (; i <= j; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << '\n';
	}


	T& Get(const size_t& i)
	{
		assert(i < count);


		return arr[i];
	}


	T PopBack()
	{
		const size_t fourthSize = maxSize / 4;
		if (count - 1 == fourthSize && fourthSize > 4)
			HalfSize();

		return arr[count--];
	}


	bool IsEmpty() const
	{
		if (maxSize == 0)
			return true;
		return false;
	}


	size_t Find(const T& item)
	{
		for (uint i = 0; i < count; i++)
		{
			if (arr[i] == item)
			{
				return i;
			}
		}
		//not found
		return count;
	}


	bool Contains(const T& item)
	{
		for (uint i = 0; i < count; i++)
		{
			if (arr[i] == item)
			{
				return true;
			}
		}
		return false;
	}

	void Insert(size_t index, const T& item)
	{
		if (index == count)
			PushBack(item);
		else
		{
			if (count == maxSize)
				DoubleSize();
			count++;
			T toAdd = arr[index];
			T lastItem;
			for (size_t i = index + 1; i < count; i++)
			{
				lastItem = arr[i];
				arr[i] = toAdd;
				toAdd = lastItem;
			}
			arr[index] = item;
		}
	}


	void Prepend(const T& item)
	{
		Insert(0, item);
	}


	void Remove(const T& item)
	{
		T* aux = new T[count];
		uint newCount = 0;
		uint auxIndex = 0;
		for (uint i = 0; i < count; i++)
		{
			if (arr[i] != item)
			{
				aux[auxIndex++] = arr[i];
				newCount++;
			}
		}

		count = newCount;

		for (uint i = 0; i < count; i++)
		{
			arr[i] = aux[i];
		}
		delete[]aux;
	}


	void RemoveAtIndex(const size_t& index)
	{
		if (count == 0)
			return;
		count--;
		for (size_t i = index; i < count; i++)
		{
			arr[i] = arr[i + 1];
		}
	}


	void RemoveAll()
	{
		count = 0;
	}


	void Resize(const size_t size)
	{
		arr = new T[size];
		this->maxSize = size;
	}

private:
	T* arr = nullptr;
	size_t maxSize = 0;
	size_t count = 0;
};
