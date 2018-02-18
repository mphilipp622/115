#pragma once
#include <cstdlib>
#include <cmath>
#include <type_traits>

namespace ArrayMaker
{
	template<typename T>
	T* RandomArray(int length)
	{
		T *arr = new T[length];

		if (std::is_floating_point<T>::value)
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

		return arr;
	}

	template<typename T>
	T* ReverseArray(int length)
	{
		T* arr = new T[length];

		T j = (T)length;

		for (int i = 0; i < length; i++, j--)
			arr[i] = j; // created sorted array

		return arr;
	}

	template<typename T>
	T* OrderedArray(int length)
	{
		T* arr = new T[length];

		for (int i = 0; i < length; i++)
			arr[i] = (T)i; // created sorted array


		return arr;
	}

	template<typename T>
	T* ShuffleArray(int length)
	{
		T* arr = new T[length];

		int cap = length * 0.1; // 10% of the length

		for (int i = 0; i < length; i++)
			// Initialize an ordered array first.
			arr[i] = (T)i;

		for (int i = 0; i < cap; i++)
		{
			// shuffle 10% of the array
			int randIndex = rand() % length;
			Swap(arr, i, randIndex);
		}

		return arr;
	}

	template<typename T>
	void Swap(T* arr, int i, int j)
	{
		T temp;
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	template<typename T>
	void DisplayArray(T* arr, int length)
	{
		for (int i = 0; i < length; i++)
			cout << arr[i] << endl;
	}
}
