/*
Mark Philipp
CSCI 115
ID: 109941708
*/

#pragma once
#include "stdafx.h"
#include "Array.h"
#include <iostream>
#include <type_traits>
#include "Timer.h"
#include <fstream>
#include "Sort.h"

using namespace std;
using namespace Timer; // Use custom timer namespace for timing benchmarks
using namespace Sort; // use custom Sort namespace for sorting algorithms

// Created a namespace for the different types of arrays. This isn't necessary but helps me with organization
namespace ArrayTemplate
{

	// This class will create ordered arrays. Inherits from Array prototype class.
	// Note that c++ linkers do not work well when implementations are defined in .cpp files for template classes.
	// To resolve the issue, I put the implementations inside the header file
	template<typename T>
	class OrderedArray : public Array<T>
	{

	public:

		// Clone function for Prototype design pattern
		Array<T>* Clone()
		{
			return new OrderedArray<T>(size, choice, type);
		}

		// Preferred constructor for OrderedArray
		OrderedArray(int newSize, int choice, int type)
		{
			// Keep track of the size, choice, and type for benchmarking and sorting in main
			this->size = newSize;
			this->choice = choice;
			this->type = type;
			
			// allocate memory for this array
			this->arr = (T*)malloc(sizeof(T) * size);

			// initialize starting value. Set it as floating point so that floats/doubles are handled.
			// int will implicitly cast, which is fine.
			T value = (T)0.0;

			if (_Is_character<T>::value)
				// handle the case where type T is char.
				value = (T)65; // ASCII value for 'A'

			for (int i = 0; i < size; i++, value += 1.0)
				this->arr[i] = value; // populate ordered array
		}

		// Destructor will delete the array from memory
		~OrderedArray()
		{
			delete this->arr;
		}

		// Outputs the contents of the array to the console.
		void DisplayArray()
		{
			if (is_floating_point<T>::value)
				// if the type is floating point, show decimals
				cout << fixed;

			for (int i = 0; i < size; i++)
				std::cout << this->arr[i] << std::endl;
		}

		/* 
		Keeps track of running time for sorting this array. Outputs running information to console and
		opens output files and writes time data to them so I can easily bring the data into Excel for analysis.
		*/
		void Benchmark(string method)
		{
			ofstream output;

			// open a CSV file in the Data folder. Filename is <SortedTyped><SortMethod><ArraySize>.csv
			// CSV files are preferred because they put data into cells that can be read in Excel.
			output.open("Data/Ordered" + method + to_string(size) + ".csv");

			output << "Random" << endl; // set column name in csv file
			cout << "Starting " << method << size << endl; // print console message to indicate benchmark is starting

			auto startTotal = chrono::system_clock::now(); // timer will keep track of total running time
			auto checkThreshold = chrono::system_clock::now(); // threshold will check if we exceed a max running time

			// note that we don't have to create copies of an ordered array since it will never be altered by sorting
			for (int i = 0; i < 100 && !HasExceededTimeThreshold(checkThreshold, 7200); i++)
			{
				// run sorting method 100 times and output running time to our csv file
				// If the total running time exceeds 2 hours, then we quit and will make note of this in the report.

				cout << "Ordered " << method << " " << i << endl;

				auto start = chrono::system_clock::now(); // start timer for this iteration

				// execute the sorting method requested
				if (method == "BubbleSort")
					BubbleSort<T>(arr, size);
				else if (method == "InsertionSort")
					InsertionSort<T>(arr, size);
				else if (method == "SelectionSort")
					SelectionSort<T>(arr, size);
				else if (method == "QuickSort")
					QuickSort<T>(arr, 0, size - 1);
				else if (method == "MergeSort")
					MergeSort<T>(arr, 0, size - 1);

				auto end = chrono::system_clock::now(); // grab time after sorting

				chrono::duration<double> elapsed = end - start; // get elapsed time

				output << std::fixed << std::setprecision(10);
				output << elapsed.count() << endl; // write elapsed time to csv file

				cout << std::fixed << std::setprecision(10);
				cout << "Finished in " << elapsed.count() << "s" << endl;
			}

			output.close();

			auto endTotal = chrono::system_clock::now();
			chrono::duration<double> elapsedTotal = endTotal - startTotal; // get total time elapsed

			cout << endl;

			if (HasExceededTimeThreshold(checkThreshold, 7200))
				std::cout << "Ordered " << method << " Size " << size << " Exceeded 120 minutes of execution. Aborting" << endl;
			else
				std::cout << "Ordered " << method << " Size " << size << " Finished in " << elapsedTotal.count() << "s" << endl;
		}

		// Public Getter for the array's data
		T* GetData()
		{
			return this->arr;
		}

	private:
		// array's data
		T* arr;
	};
}