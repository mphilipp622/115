#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <type_traits>

using namespace std;

/*
This class will create Random arrays. Inherits from Array prototype class
*/
template<typename T>
class RandomArray : public Array
{
public:
	Array* Clone()
	{
		return new RandomArray<T>;
	}

	RandomArray(int newSize)
	{
		this->size = newSize;
		arr = (T*)malloc(sizeof(T) * size);
		srand(time(NULL));

		if (is_floating_point<T>::value)
		{
			// handles floating point random numbers
			for (int i = 0; i < length; i++)
				arr[i] = fmod((rand() / (T)RAND_MAX) * (length * 5), (length * 5));
		}
		else
		{
			for (int i = 0; i < length; i++)
				arr[i] = rand() % (length * 5);
		}
	}

	~RandomArray()
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

