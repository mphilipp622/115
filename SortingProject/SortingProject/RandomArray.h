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
	class RandomArray : public Array
	{
	public:
		Array* Clone()
		{
			return new RandomArray<T>(size);
		}

		RandomArray(int newSize)
		{
			this->size = newSize;
			arr = (T*)malloc(sizeof(T) * size);
			srand(time(NULL));

			if (is_floating_point<T>::value)
			{
				// handles floating point random numbers
				for (int i = 0; i < newSize; i++)
					arr[i] = fmod((rand() / (T)RAND_MAX) * (newSize * 5), (newSize * 5));
			}
			else if (_Is_character<T>::value)
			{
				// handles character values
				for (int i = 0; i < newSize; i++)
					arr[i] = rand() % (122 - 65) + 65; // set boundaries for ASCII table
			}
			else
			{
				for (int i = 0; i < newSize; i++)
					arr[i] = rand() % (newSize * 5);
			}
		}

		~RandomArray()
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
	};

}