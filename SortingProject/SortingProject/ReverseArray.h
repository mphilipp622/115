#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>

using namespace std;

/*
This class will create reverse arrays. Inherits from Array prototype class
*/
template<typename T>
class ReverseArray : public Array
{
public:
	Array* Clone()
	{
		return new ReverseArrray<T>;
	}

	ReverseArray(int newSize)
	{
		this->size = newSize;
		arr = (T*)malloc(sizeof(T) * size);
		T value = 0.0;

		for (int i = this->size - 1; i > -1; i--)
			arr[i] = value; // populate reverse array
	}

	~ReverseArray()
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

