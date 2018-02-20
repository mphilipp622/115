#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>

using namespace std;

/*
This class will create ordered arrays. Inherits from Array prototype class.
*/
template<typename T>
class OrderedArray : public Array
{
public:
	Array* Clone()
	{
		return new OrderedArray<T>;
	}

	OrderedArray(int newSize)
	{
		this->size = newSize;
		arr = (T*)malloc(sizeof(T) * size);
		T value = 0.0;

		for (int i = 0; i < this->size; i++, value++)
			arr[i] = value; // populate ordered array
	}

	~OrderedArray()
	{
		delete arr;
	}

	void DisplayArray()
	{
		for (int i = 0; i < this->size; i++)
			cout << arr[i] << endl;
	}

	T operator[](int index)
	{
		return arr[index];
	}

private:
	T* arr;
};