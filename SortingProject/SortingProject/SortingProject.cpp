#include "stdafx.h"
#include "Benchmarker.h"

using namespace std;
using namespace Benchmarker;

int main()
{

	// Bubble Sort Benchmarks
	BenchmarkBubbleSort(10);
	BenchmarkBubbleSort(1000);
	BenchmarkBubbleSort(10000);
	BenchmarkBubbleSort(100000);
	BenchmarkBubbleSort(1000000);

	// Selection Sort Benchmarks
	BenchmarkSelectionSort(10);
	BenchmarkSelectionSort(1000);
	BenchmarkSelectionSort(10000);
	BenchmarkSelectionSort(100000);
	BenchmarkSelectionSort(1000000);

	// insertion sort benchmarks
	BenchmarkInsertionSort(10);
	BenchmarkInsertionSort(1000);
	BenchmarkInsertionSort(10000);
	BenchmarkInsertionSort(100000);
	BenchmarkInsertionSort(1000000);

	// Merge Sort Benchmarks
	BenchmarkMergeSort(10);
	BenchmarkMergeSort(1000);
	BenchmarkMergeSort(10000);
	BenchmarkMergeSort(100000);
	BenchmarkMergeSort(1000000);

	// Quick Sort Benchmarks
	BenchmarkQuickSort(10);
	BenchmarkQuickSort(1000);
	BenchmarkQuickSort(10000);
	BenchmarkQuickSort(100000);
	BenchmarkQuickSort(1000000);

	return 0;
}
