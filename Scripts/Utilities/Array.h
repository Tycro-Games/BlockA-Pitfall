#pragma once
//https://en.cppreference.com/w/cpp/language/operators


template <class T>
class Array
{
public:
	~Array();
	void Init(size_t _count);
	size_t GetCount() const;
	T& operator [](size_t index);
	T& Get(size_t index);
private:
	T* cell = nullptr;
	size_t count = 0;
};

