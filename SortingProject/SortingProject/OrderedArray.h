#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <type_traits>

using namespace std;

namespace ArrayTemplate
{
	/*
	This class will create ordered arrays. Inherits from Array prototype class.
	*/
	template<typename T>
	class OrderedArray : public Array
	{
	public:
		Array* Clone()
		{
			return new OrderedArray<T>(size);
		}

		OrderedArray(int newSize)
		{

			this->size = newSize;
			arr = (T*)malloc(sizeof(T) * size);

			T value = (T)1.0;

			if (_Is_character<T>::value)
				value = (T)65; // ASCII value for 'A'

			for (int i = 0; i < this->size; i++, value += 1.0)
				arr[i] = value; // populate ordered array
		}

		~OrderedArray()
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