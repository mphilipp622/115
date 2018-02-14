#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include "Sorter.h"
#include <fstream>
#include <string>

using namespace std;
using namespace Sorter;


namespace Benchmarker
{
	// Will use ofstream to output data to a CSV file. Columns are separated by commas and rows are separated by \n
	bool HasExceededTimeThreshold(chrono::time_point<chrono::system_clock> start)
	{
		// time threshold will be set at 120 minutes total.
		// If any algorithm runs longer than 120 minutes, than we will quit execution.
		auto end = chrono::system_clock::now();
		chrono::duration<double> elapsed = end - start;

		if (elapsed.count() >= 7200)
			return true;

		return false;
	}

	void Benchmark(string method, int size)
	{
		ofstream output;

		//////////////////
		// random array //
		//////////////////

		srand(time(NULL)); // set new seed. Can't call in loop or else we get the same seeds

		output.open("Data/" + method + to_string(size) + ".csv");
		int* arrOriginal = RandomArray(size); // get new random array
		int* arr = new int[size];

		output << "Random" << endl; // set column name
		cout << "Starting " << method << size << endl;
		auto startTotal = chrono::system_clock::now();
		auto checkThreshold = chrono::system_clock::now();

		for (int i = 0; i < 100 && !HasExceededTimeThreshold(checkThreshold); i++)
		{
			cout << method << " Random COUNT " << i << endl;
			memcpy(arr, arrOriginal, size * sizeof(int)); // copy data so we maintain the exact same data per iteration

			auto start = chrono::system_clock::now(); // start timer

			if (method == "BubbleSort")
				BubbleSort(arr, size);
			else if (method == "InsertionSort")
				InsertionSort(arr, size);
			else if (method == "SelectionSort")
				SelectionSort(arr, size);
			else if (method == "QuickSort")
				QuickSort(arr, 0, size - 1);
			else if (method == "MergeSort")
				MergeSort(arr, 0, size - 1);

			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		///////////////////
		// ordered array //
		///////////////////

		//output.open("Data/BubbleSortOrdered" + to_string(size) + ".csv");
		arrOriginal = OrderedArray(size);
		//memcpy(arr, arrOriginal, size * sizeof(int));
		output << ",Ordered" << endl;

		checkThreshold = chrono::system_clock::now();

		for (int i = 0; i < 100 && !HasExceededTimeThreshold(checkThreshold); i++)
		{
			// don't need to copy data for an ordered array. It's always gonna be the same every time.
			cout << method << " Ordered COUNT " << i << endl;
			auto start = chrono::system_clock::now(); // start timer

			if (method == "BubbleSort")
				BubbleSort(arrOriginal, size);
			else if (method == "InsertionSort")
				InsertionSort(arrOriginal, size);
			else if (method == "SelectionSort")
				SelectionSort(arrOriginal, size);
			else if (method == "QuickSort")
				QuickSort(arrOriginal, 0, size - 1);
			else if (method == "MergeSort")
				MergeSort(arrOriginal, 0, size - 1);

			auto end = chrono::system_clock::now();


			chrono::duration<double> elapsed = end - start;

			//output << std::fixed << std::setprecision(10);
			output << "," << elapsed.count() << endl;
		}
		
		///////////////////
		// reverse array //
		///////////////////

		arrOriginal = ReverseArray(size); // reverse the array
		output << ",,Reverse" << endl;
		checkThreshold = chrono::system_clock::now();

		for (int i = 0; i < 100 && !HasExceededTimeThreshold(checkThreshold); i++)
		{
			cout << method << " Reverse COUNT " << i << endl;
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer

			if (method == "BubbleSort")
				BubbleSort(arr, size);
			else if (method == "InsertionSort")
				InsertionSort(arr, size);
			else if (method == "SelectionSort")
				SelectionSort(arr, size);
			else if (method == "QuickSort")
				QuickSort(arr, 0, size - 1);
			else if (method == "MergeSort")
				MergeSort(arr, 0, size - 1);

			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",," << elapsed.count() << endl;
		}

		///////////////////
		// shuffle array //
		///////////////////

		arrOriginal = ShuffleTen(size); // reverse the array
		output << ",,,Shuffle" << endl;
		checkThreshold = chrono::system_clock::now();

		for (int i = 0; i < 100 && !HasExceededTimeThreshold(checkThreshold); i++)
		{
			cout << method << " Shuffle COUNT " << i << endl;
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer

			if (method == "BubbleSort")
				BubbleSort(arr, size);
			else if (method == "InsertionSort")
				InsertionSort(arr, size);
			else if (method == "SelectionSort")
				SelectionSort(arr, size);
			else if (method == "QuickSort")
				QuickSort(arr, 0, size - 1);
			else if (method == "MergeSort")
				MergeSort(arr, 0, size - 1);

			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",,," << elapsed.count() << endl;
		}

		output.close();
		auto endTotal = chrono::system_clock::now();
		chrono::duration<double> elapsedTotal = endTotal - startTotal;

		/*delete arr;
		delete arrOriginal;*/

		if (HasExceededTimeThreshold(checkThreshold))
			std::cout << method << size << " Exceeded 120 minutes of execution. Aborting" << endl;
		else
			std::cout << method << size << " Finished in " << elapsedTotal.count() << "s" << endl;
	}
}