#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include "Sorter.h"

using namespace std;
using namespace Sorter;

// macros for string parsing


namespace Benchmarker
{
	void BenchmarkBubbleSort(int size)
	{
		cout << "Benchmarking Bubble Sort on array size " << size << endl;

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
			auto end = chrono::system_clock::now();
			
			chrono::duration<double> elapsed = end - start;

			std::cout << std::fixed << std::setprecision(10);
			std::cout << elapsed.count() << std::endl;
		}
	}

	void BenchmarkSelectionSort(int size)
	{
		cout << "Benchmarking Selection Sort on array size " << size << endl;

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			std::cout << std::fixed << std::setprecision(10);
			std::cout << elapsed.count() << std::endl;
		}
	}

	void BenchmarkInsertionSort(int size)
	{
		cout << "Benchmarking Insertion Sort on array size " << size << endl;

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			std::cout << std::fixed << std::setprecision(10);
			std::cout << elapsed.count() << std::endl;
		}
	}

	void BenchmarkMergeSort(int size)
	{
		cout << "Benchmarking Merge Sort on array size " << size << endl;

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			std::cout << std::fixed << std::setprecision(10);
			std::cout << elapsed.count() << std::endl;
		}
	}

	void BenchmarkQuickSort(int size)
	{
		cout << "Benchmarking Quick Sort on array size " << size << endl;

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			std::cout << std::fixed << std::setprecision(10);
			std::cout << elapsed.count() << std::endl;
		}
	}
}