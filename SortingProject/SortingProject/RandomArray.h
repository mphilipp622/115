#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <type_traits>
#include "Timer.h"
#include "Sort.h"
#include <fstream>


using namespace std;
using namespace Timer;
using namespace Sort;

namespace ArrayTemplate
{
	/*
	This class will create Random arrays. Inherits from Array prototype class
	*/
	template<typename T>
	class RandomArray : public Array<T>
	{
	public:
		Array<T>* Clone()
		{
			return new RandomArray<T>(size, choice, type);
		}

		RandomArray(int newSize, int choice, int type)
		{
			this->size = newSize;
			this->choice = choice;
			this->type = type;

			arr = (T*)malloc(sizeof(T) * size);
			srand(time(NULL));

			if (is_floating_point<T>::value)
			{
				// handles floating point random numbers
				for (int i = 0; i < newSize; i++)
					this->arr[i] = fmod((rand() / (T)RAND_MAX) * (newSize * 5), (newSize * 5));
			}
			else if (_Is_character<T>::value)
			{
				// handles character values
				for (int i = 0; i < newSize; i++)
					this->arr[i] = (T)(rand() % (122 - 65) + 65); // set boundaries for ASCII table
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

		void Benchmark(string method)
		{
			ofstream output;

			output.open("Data/Random" + method + to_string(size) + ".csv");

			output << "Random" << endl; // set column name
			cout << "Starting " << method << size << endl;
			auto startTotal = chrono::system_clock::now();
			auto checkThreshold = chrono::system_clock::now();

			for (int i = 0; i < 100 && !HasExceededTimeThreshold(checkThreshold, 7200); i++)
			{
				cout << method << " Random COUNT " << i << endl;
				auto* arrCopy = ArrayFactory::MakeClone<T>(choice, type, size);

				//memcpy(arr, arrOriginal, size * sizeof(int)); // copy data so we maintain the exact same data per iteration
				auto start = chrono::system_clock::now(); // start timer

				if (method == "BubbleSort")
					BubbleSort<T>(arrCopy->GetData(), size);
				else if (method == "InsertionSort")
					InsertionSort<T>(arrCopy->GetData(), size);
				else if (method == "SelectionSort")
					SelectionSort<T>(arrCopy->GetData(), size);
				else if (method == "QuickSort")
					QuickSort<T>(arrCopy->GetData(), 0, size - 1);
				else if (method == "MergeSort")
					MergeSort<T>(arrCopy->GetData(), 0, size - 1);

				auto end = chrono::system_clock::now();

				chrono::duration<double> elapsed = end - start;
				arrCopy->DisplayArray();
				output << std::fixed << std::setprecision(10);
				output << elapsed.count() << endl;
			}

			output.close();
			auto endTotal = chrono::system_clock::now();
			chrono::duration<double> elapsedTotal = endTotal - startTotal;

			if (HasExceededTimeThreshold(checkThreshold, 7200))
				std::cout << method << size << " Exceeded 120 minutes of execution. Aborting" << endl;
			else
				std::cout << method << size << " Finished in " << elapsedTotal.count() << "s" << endl;
		}

		T* GetData()
		{
			return arr;
		}

	private:
		T* arr;
	};

}