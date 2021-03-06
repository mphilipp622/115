/*
Mark Philipp
Isaac Fielding
CSCI 115
*/

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

// Created a namespace for the different types of arrays. This isn't necessary but helps me with organization
namespace ArrayTemplate
{

	// This class will create random arrays. Inherits from Array prototype class.
	// Note that c++ linkers do not work well when implementations are defined in .cpp files for template classes.
	// To resolve the issue, I put the implementations inside the header file
	template<typename T>
	class RandomArray : public Array<T>
	{

	public:

		// Clone function for Prototype design pattern
		Array<T>* Clone()
		{
			return new RandomArray<T>(size, choice, type);
		}

		// Preferred constructor for RandomArray
		RandomArray(int newSize, int choice, int type)
		{
			// Keep track of the size, choice, and type for benchmarking and sorting in main
			this->size = newSize;
			this->choice = choice;
			this->type = type;

			this->arr = (T*)malloc(sizeof(T) * size); // allocate memory for this array
			srand(time(NULL)); // initialize random seed

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
					this->arr[i] = rand() % (newSize * 5);
			}
		}

		// destructor will delete array from memory
		~RandomArray()
		{
			delete this->arr;
		}

		// Outputs the contents of the array to the console
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
			output.open("Data/Random" + method + to_string(size) + ".csv");

			output << "Random" << endl; // set column name
			cout << "Starting " << method << size << endl; // print console message to indicate benchmark is starting
			
			auto startTotal = chrono::system_clock::now(); // timer will keep track of total running time 
			auto checkThreshold = chrono::system_clock::now(); // threshold will check if we exceed a max running time

			for (int i = 0; i < 100 && !HasExceededTimeThreshold(checkThreshold, 7200); i++)
			{
				// run sorting method 100 times and output running time to our csv file
				// If the total running time exceeds 2 hours, then we quit and will make note of this in the report.

				cout << "Random " << method << " " << i << endl;

				// Create a clone of the array using prototype pattern. 
				// This makes sure we have the same data to sort every iteration
				auto* arrCopy = ArrayFactory::MakeClone<T>(choice, type, size);

				auto start = chrono::system_clock::now(); // start timer for this iteration

				// execute the sorting method requested
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

				auto end = chrono::system_clock::now(); // grab time after sorting

				chrono::duration<double> elapsed = end - start; // get elapsed time
				
				output << std::fixed << std::setprecision(10);
				output << elapsed.count() << endl; // write elapsed time to csv file

				cout << std::fixed << std::setprecision(10);
				cout << "Finished in " << elapsed.count() << "s" << endl;

				delete arrCopy; // free memory
			}

			output.close();

			auto endTotal = chrono::system_clock::now();
			chrono::duration<double> elapsedTotal = endTotal - startTotal; // get total time elapsed

			cout << endl;

			if (HasExceededTimeThreshold(checkThreshold, 7200))
				std::cout << "Random " << method << " Size " << size << " Exceeded 120 minutes of execution. Aborting" << endl;
			else
				std::cout << "Random " << method << " Size " << size << " Finished in " << elapsedTotal.count() << "s" << endl;
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