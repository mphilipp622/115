#pragma once
#include <string>

// Namespace for benchmarking sorting functions. Pass sizes to the functions and they'll call on
// Sorter.h to execute sorting and output times to a console window.
namespace Benchmarker
{

	void Benchmark(std::string method, int size);
	// Returns the time it takes to run Bubble Sort on array arr. Runs 100 times.
	void BenchmarkBubbleSort(int size);

	// Returns the time it takes to run Selection Sort on array arr. Runs 100 times.
	void BenchmarkSelectionSort(int size);

	// Returns the time it takes to run Insertion Sort on array arr. Runs 100 times.
	void BenchmarkInsertionSort(int size);

	// Returns the time it takes to run Merge Sort on array arr. Runs 100 times.
	void BenchmarkMergeSort(int size);

	// Returns the time it takes to run Quick Sort on array arr. Runs 100 times.
	void BenchmarkQuickSort(int size);
}