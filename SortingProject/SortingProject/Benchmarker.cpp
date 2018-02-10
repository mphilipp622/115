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

// macros for string parsing


namespace Benchmarker
{

	void BenchmarkBubbleSort(int size)
	{
		ofstream output;

		//////////////////
		// random array //
		//////////////////

		srand(time(NULL)); // set new seed. Can't call in loop or else we get the same seeds

		output.open("Data/BubbleSortRandom" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// ordered array //
		///////////////////

		output.open("Data/BubbleSortOrdered" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = OrderedArray(size);

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// reverse array //
		///////////////////

		output.open("Data/BubbleSortReversed" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ReverseArray(size);

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// shuffle array //
		///////////////////

		output.open("Data/BubbleSortShuffle" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ShuffleTen(size);

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();


	}

	void BenchmarkSelectionSort(int size)
	{
		ofstream output;
		
		//////////////////
		// random array //
		//////////////////

		srand(time(NULL)); // set new seed. Can't call in loop or else we get the same seeds

		output.open("Data/SelectionSortRandom" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// ordered array //
		///////////////////

		output.open("Data/SelectionSortOrdered" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = OrderedArray(size);

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();
		
		///////////////////
		// reverse array //
		///////////////////

		output.open("Data/SelectionSortReversed" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ReverseArray(size);

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();
		
		///////////////////
		// shuffle array //
		///////////////////

		output.open("Data/SelectionSortShuffle" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ShuffleTen(size);

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

	}

	void BenchmarkInsertionSort(int size)
	{
		ofstream output;

		//////////////////
		// random array //
		//////////////////

		srand(time(NULL)); // set new seed. Can't call in loop or else we get the same seeds

		output.open("Data/InsertionSortRandom" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// ordered array //
		///////////////////

		output.open("Data/InsertionSortOrdered" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = OrderedArray(size);

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// reverse array //
		///////////////////

		output.open("Data/InsertionSortReversed" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ReverseArray(size);

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// shuffle array //
		///////////////////

		output.open("Data/InsertionSortShuffle" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ShuffleTen(size);

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();
	}

	void BenchmarkMergeSort(int size)
	{
		ofstream output;

		//////////////////
		// random array //
		//////////////////

		srand(time(NULL)); // set new seed. Can't call in loop or else we get the same seeds

		output.open("Data/MergeSortRandom" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// ordered array //
		///////////////////

		output.open("Data/MergeSortOrdered" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = OrderedArray(size);

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// reverse array //
		///////////////////

		output.open("Data/MergeSortReversed" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ReverseArray(size);

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// shuffle array //
		///////////////////

		output.open("Data/MergeSortShuffle" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ShuffleTen(size);

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();
	}

	void BenchmarkQuickSort(int size)
	{
		ofstream output;

		//////////////////
		// random array //
		//////////////////

		srand(time(NULL)); // set new seed. Can't call in loop or else we get the same seeds

		output.open("Data/QuickSortRandom" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = RandomArray(size); // get new random array

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// ordered array //
		///////////////////

		output.open("Data/QuickSortOrdered" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = OrderedArray(size);

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// reverse array //
		///////////////////

		output.open("Data/QuickSortReversed" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ReverseArray(size);

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();

		///////////////////
		// shuffle array //
		///////////////////

		output.open("Data/QuickSortShuffle" + to_string(size) + ".csv");

		for (int i = 0; i < 100; i++)
		{
			int* arr = ShuffleTen(size);

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		output.close();
	}
}