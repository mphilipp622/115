// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Benchmarker.h"

using namespace std;
using namespace Benchmarker;

int main()
{
	while (!cin.eof())
	{
		int method, size = 0;
		cout << "Select Sorting Method: 1. Bubble Sort, 2. Insertion Sort, 3. Selection Sort, 4. Quick Sort, 5. Merge Sort:";
		cin >> method;

		cout << endl << "Select Size To Test:";
		cin >> size;
		cout << endl;

		if (method == 1)
			BenchmarkBubbleSort(size);
		else if (method == 2)
			BenchmarkInsertionSort(size);
		else if (method == 3)
			BenchmarkSelectionSort(size);
		else if (method == 4)
			BenchmarkQuickSort(size);
		else if (method == 5)
			BenchmarkMergeSort(size);

		cout << endl;
	}

	return 0;
}
