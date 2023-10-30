#pragma once
//https://en.cppreference.com/w/cpp/language/operators
//https://www.3dgep.com/beginning-cpp-template-programming/

template <class T>
class StaticArray
{
public:
	StaticArray() = default;


	~StaticArray()
	{
		//how to solve for the pointer to pointer case?
		delete[] data;
	}

	void Init(size_t _count)
	{
		data = new T[_count];
		count = _count;
	}

	size_t Size() const
	{
		return count;
	}

	T& operator[](const size_t index)
	{
		assert(index < count);
		return data[index];
	}

	const T& operator[](const size_t index) const
	{
		assert(index < count);
		return data[index];
	}

private:
	T* data = nullptr;
	size_t count = 0;
};
