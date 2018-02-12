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

		for (int i = 0; i < 100; i++)
		{
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
		memcpy(arr, arrOriginal, size * sizeof(int));
		output << ",Ordered" << endl;

		for (int i = 0; i < 100; i++)
		{
			// don't need to copy data for an ordered array. It's always gonna be the same every time.

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

			//output << std::fixed << std::setprecision(10);
			output << "," << elapsed.count() << endl;
		}

		///////////////////
		// reverse array //
		///////////////////

		arrOriginal = ReverseArray(size); // reverse the array
		output << ",,Reverse" << endl;

		for (int i = 0; i < 100; i++)
		{
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

		for (int i = 0; i < 100; i++)
		{
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

		cout << method << size << " Finished in " << elapsedTotal.count() << "s" << endl;
	}
	void BenchmarkBubbleSort(int size)
	{
		ofstream output;

		//////////////////
		// random array //
		//////////////////
		
		srand(time(NULL)); // set new seed. Can't call in loop or else we get the same seeds

		output.open("Data/BubbleSort" + to_string(size) + ".csv");
		int* arrOriginal = RandomArray(size); // get new random array
		int* arr = new int[size];

		output << "Random" << endl; // set column name

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int)); // copy data so we maintain the exact same data per iteration

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
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
		memcpy(arr, arrOriginal, size * sizeof(int));
		output << ",Ordered" << endl;

		for (int i = 0; i < 100; i++)
		{
			// don't need to copy data for an ordered array. It's always gonna be the same every time.

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
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

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
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

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			BubbleSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",,," << elapsed.count() << endl;
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

		output.open("Data/SelectionSort" + to_string(size) + ".csv");
		int* arrOriginal = RandomArray(size); // get new random array
		int* arr = new int[size];
		output << "Random" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}


		///////////////////
		// ordered array //
		///////////////////

		arrOriginal = OrderedArray(size);
		memcpy(arr, arrOriginal, size * sizeof(int));
		output << ",Ordered" << endl;

		for (int i = 0; i < 100; i++)
		{

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << "," << elapsed.count() << endl;
		}

		
		///////////////////
		// reverse array //
		///////////////////

		arrOriginal = ReverseArray(size);
		output << ",,Reversed" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",," << elapsed.count() << endl;
		}
		
		///////////////////
		// shuffle array //
		///////////////////

		arrOriginal = ShuffleTen(size);
		output << ",,,Shuffled" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			SelectionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",,," << elapsed.count() << endl;
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

		output.open("Data/InsertionSort" + to_string(size) + ".csv");
		output << "Random" << endl;

		int* arrOriginal = RandomArray(size);
		int* arr = new int[size];

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}


		///////////////////
		// ordered array //
		///////////////////
		arrOriginal = OrderedArray(size);
		memcpy(arr, arrOriginal, size * sizeof(int));

		output << ",Ordered" << endl;

		for (int i = 0; i < 100; i++)
		{

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << "," << elapsed.count() << endl;
		}

		///////////////////
		// reverse array //
		///////////////////

		arrOriginal = ReverseArray(size);
		output << ",,Reversed" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",," << elapsed.count() << endl;
		}

		///////////////////
		// shuffle array //
		///////////////////

		arrOriginal = ShuffleTen(size);
		output << ",,,Shuffled" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			InsertionSort(arr, size);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",,," << elapsed.count() << endl;
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

		output.open("Data/MergeSort" + to_string(size) + ".csv");
		output << "Random" << endl;
		int* arrOriginal = RandomArray(size);
		int* arr = new int[size];

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		///////////////////
		// ordered array //
		///////////////////

		output << ",Ordered" << endl;

		arrOriginal = OrderedArray(size);
		memcpy(arr, arrOriginal, size * sizeof(int));

		for (int i = 0; i < 100; i++)
		{

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << "," << elapsed.count() << endl;
		}

		///////////////////
		// reverse array //
		///////////////////

		arrOriginal = ReverseArray(size);
		output << ",,Reversed" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",," << elapsed.count() << endl;
		}

		///////////////////
		// shuffle array //
		///////////////////

		arrOriginal = ShuffleTen(size);
		output << ",,,Shuffled" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			MergeSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",,," << elapsed.count() << endl;
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

		output.open("Data/QuickSort" + to_string(size) + ".csv");
		output << "Random" << endl;

		int* arrOriginal = RandomArray(size);
		int* arr = new int[size];

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << elapsed.count() << endl;
		}

		///////////////////
		// ordered array //
		///////////////////

		arrOriginal = OrderedArray(size);
		memcpy(arr, arrOriginal, size * sizeof(int));

		output << ",Ordered" << endl;

		for (int i = 0; i < 100; i++)
		{
			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << "," << elapsed.count() << endl;
		}

		///////////////////
		// reverse array //
		///////////////////

		output << ",,Reversed" << endl;
		arrOriginal = ReverseArray(size);

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",," << elapsed.count() << endl;
		}

		///////////////////
		// shuffle array //
		///////////////////

		arrOriginal = ShuffleTen(size);
		output << ",,,Shuffled" << endl;

		for (int i = 0; i < 100; i++)
		{
			memcpy(arr, arrOriginal, size * sizeof(int));

			auto start = chrono::system_clock::now(); // start timer
			QuickSort(arr, 0, size - 1);
			auto end = chrono::system_clock::now();

			chrono::duration<double> elapsed = end - start;

			output << std::fixed << std::setprecision(10);
			output << ",,," << elapsed.count() << endl;
		}

		output.close();
	}
}