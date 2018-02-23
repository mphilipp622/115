#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>

using namespace std;

namespace ArrayTemplate
{
	/*
	This class will create reverse arrays. Inherits from Array prototype class
	*/
	template<typename T>
	class ReverseArray : public Array
	{
	public:
		Array* Clone()
		{
			return new ReverseArray<T>(size);
		}

		ReverseArray(int newSize)
		{
			this->size = newSize;
			arr = (T*)malloc(sizeof(T) * size);
			T value = 0.0;

			if (_Is_character<T>::value)
				value = (T)65; // ASCII value for 'A'

			for (int i = this->size - 1; i > -1; i--, value++)
				arr[i] = value; // populate reverse array
		}

		~ReverseArray()
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