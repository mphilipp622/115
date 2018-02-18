#include "stdafx.h"
#include "Benchmarker.h"
#include <iostream>
#include "Sorter.h"
#include "ArrayMaker.h"

using namespace std;
using namespace Benchmarker;
using namespace Sorter;
using namespace ArrayMaker;

int main()
{
	auto* arr = ReverseArray<double>(10);
	DisplayArray(arr, 10);
	//int* arr = RandomArray<int>(10);
	//DisplayArray(arr, 10);
	/*MergeSort(arr, 0, 9);
	DisplayArray(arr, 10);*/
	// size 10 arrays
	/*Benchmark("BubbleSort", 10);
	Benchmark("SelectionSort", 10);
	Benchmark("InsertionSort", 10);*/
	/*Benchmark("QuickSort", 10);
	Benchmark("MergeSort", 10);*/

	//// size 1000 arrays
	/*Benchmark("BubbleSort", 1000);
	Benchmark("SelectionSort", 1000);
	Benchmark("InsertionSort", 1000);*/
	/*Benchmark("QuickSort", 1000);
	Benchmark("MergeSort", 1000);*/

	//// size 10000 arrays
	/*Benchmark("BubbleSort", 10000);
	Benchmark("SelectionSort", 10000);
	Benchmark("InsertionSort", 10000);*/
	/*Benchmark("QuickSort", 10000);
	Benchmark("MergeSort", 10000);*/

	// size 100000 arrays
	/*Benchmark("BubbleSort", 100000);
	Benchmark("SelectionSort", 100000);
	Benchmark("InsertionSort", 100000);*/
	/*Benchmark("QuickSort", 100000);
	Benchmark("MergeSort", 100000);*/

	//// size 100000 arrays
	///*Benchmark("BubbleSort", 1000000);
	//Benchmark("SelectionSort", 1000000);
	//Benchmark("InsertionSort", 1000000);*/
	//Benchmark("QuickSort", 1000000);
	//Benchmark("MergeSort", 1000000);

	return 0;
}
