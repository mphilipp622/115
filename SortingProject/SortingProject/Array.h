#pragma once
#include <iostream>

// Base class for all array types. Implements Prototype pattern
template<typename T>
class Array
{
public:
	Array()
	{
		/*this->size = 0;
		arr = (T*)malloc(sizeof(T) * size);*/
	}
	~Array()
	{

	}

	virtual Array<T>* Clone() = 0; // prototype pattern
	int GetSize()
	{
		return this->size;
	}
	virtual void DisplayArray() = 0;

	virtual void Benchmark(std::string method) = 0;
	virtual T* GetData() = 0;

protected:
	int size, choice, type;

private:
	T* arr;
};