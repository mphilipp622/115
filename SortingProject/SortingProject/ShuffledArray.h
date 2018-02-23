#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <type_traits>

using namespace std;

namespace ArrayTemplate
{
	/*
	This class will create Random arrays. Inherits from Array prototype class
	*/
	template<typename T>
	class ShuffledArray : public Array
	{
	public:
		Array* Clone()
		{
			return new ShuffledArray<T>(size);
		}

		ShuffledArray(int newSize)
		{
			this->size = newSize;
			arr = (T*)malloc(sizeof(T) * size);

			srand(time(NULL)); // set new seed

			int cap = newSize * 0.1; // 10% of the length
			T value = 0.0;

			if (_Is_character<T>::value)
				value = (T)65; // ASCII value for 'A'

			for (int i = 0; i < newSize; i++, value++)
				// Initialize an ordered array first.
				arr[i] = value;

			for (int i = 0; i < cap; i++)
			{
				// shuffle 10% of the array
				int randIndex = rand() % newSize;
				Swap(i, randIndex);
			}
		}

		~ShuffledArray()
		{
			delete arr;
		}

		void DisplayArray()
		{
			if (is_floating_point<T>::value)
				// if the type is floating point, show decimals
				cout << fixed;

			for (int i = 0; i < size; i++)
				std::cout << arr[i] << std::endl;
		}

		T operator[](int index)
		{
			return arr[index];
		}

	private:
		T* arr;

		void Swap(int i, int j)
		{
			T temp;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	};

}