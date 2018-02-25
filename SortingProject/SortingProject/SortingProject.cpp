#include "stdafx.h"
#include <iostream>
#include "ArrayFactory.h"

using namespace std;
//using namespace Benchmarker;
//using namespace Sorter;
//using namespace ArrayMaker;

//ArrayFactory* myFactory = new ArrayFactory();

template<typename T>
void ExecuteUserCommands(Array<T>* arr, int sortSel, int benchOrSort)
{
	// Will provide output to the user based on the values they selected.
	if (benchOrSort == 1)
	{
		cout << "Before Sorting:" << endl;
		arr->DisplayArray();
		cout << endl << "After Sorting:" << endl;

		if (sortSel == 1)
			BubbleSort(arr->GetData(), arr->GetSize());
		else if (sortSel == 2)
			SelectionSort(arr->GetData(), arr->GetSize());
		else if (sortSel == 3)
			InsertionSort(arr->GetData(), arr->GetSize());
		else if (sortSel == 4)
			MergeSort(arr->GetData(), 0, arr->GetSize() - 1);
		else if (sortSel == 5)
			QuickSort(arr->GetData(), 0, arr->GetSize() - 1);

		arr->DisplayArray();

		cout << endl;
	}
	else if (benchOrSort == 2)
	{
		if (sortSel == 1)
			arr->Benchmark("BubbleSort");
		else if (sortSel == 2)
			arr->Benchmark("SelectionSort");
		else if (sortSel == 3)
			arr->Benchmark("InsertionSort");
		else if (sortSel == 4)
			arr->Benchmark("MergeSort");
		else if (sortSel == 5)
			arr->Benchmark("QuickSort");
	}
}

int main()
{
	int choiceSel = 0 , typeSel = 0, sizeSel = 0, sortSel = 0, benchOrSort = 0;

	auto* arrMain = ArrayFactory::MakeClone<char>(3, 4, 10);
	arrMain->DisplayArray();

	while (!cin.eof())
	{
		while (true)
		{
			cout << "Select a sorting algorithm" << endl;
			cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n0. Exit" << endl;
			cin >> sortSel;
			cout << endl;

			if (sortSel == 0)
				return 0;

			if (sortSel < 0 || sortSel > 5)
				cout << "ERROR: input must be 1, 2, 3, 4, 5, or 0" << endl;
			else
				break;
		}

		while (true)
		{
			cout << "Select a data type" << endl;
			cout << "1. int\n2. float\n3. double\n4. char\n0. Exit" << endl;
			cin >> typeSel;
			cout << endl;

			if (typeSel == 0)
				return 0;

			if (typeSel < 0 || typeSel > 4)
				cout << "ERROR: input must be 1, 2, 3 or 4" << endl;
			else
				break;
			
			cout << endl;
		}

		while (true)
		{
			cout << "Enter an array size (0 to exit)" << endl;
			cin >> sizeSel;
			cout << endl;

			if (sizeSel == 0)
				return 0;

			if (sizeSel < 0 || sizeSel > 1000000)
				cout << "Error: Size must be a positive value and less than 1000000" << endl;
			else
				break;

			cout << endl;
		}

		while (true)
		{
			cout << "Choose the Initial Sorting" << endl;
			cout << "1. Ordered Array\n2. ReverseArray\n3. Random Array\n4. Shuffled Array (10%)\n0. Exit" << endl;
			cin >> choiceSel;
			cout << endl;

			if (choiceSel == 0)
				return 0;

			if (choiceSel < 0 || choiceSel > 4)
				cout << "ERROR: Input must be 1, 2, 3, 4 or 0" << endl;
			else
				break;
			
			cout << endl;
		}

		while (true)
		{
			cout << "Choose What Action to Perform" << endl;
			cout << "1. Sort and Display Results\n2. Benchmark and Display Time\n0. Exit" << endl;
			cin >> benchOrSort;
			cout << endl;

			if (benchOrSort == 0)
				return 0;

			if (benchOrSort < 0 || benchOrSort > 2)
				cout << "ERROR: Selection must be 1, 2, or 0" << endl;
			else
				break;
			
			cout << endl;
		}

		if (typeSel == 1)
			ExecuteUserCommands(ArrayFactory::MakeClone<int>(choiceSel, typeSel, sizeSel), sortSel, benchOrSort);
		else if (typeSel == 2)
			ExecuteUserCommands(ArrayFactory::MakeClone<float>(choiceSel, typeSel, sizeSel), sortSel, benchOrSort);
		else if (typeSel == 3)
			ExecuteUserCommands(ArrayFactory::MakeClone<double>(choiceSel, typeSel, sizeSel), sortSel, benchOrSort);
		else if (typeSel == 4)
			ExecuteUserCommands(ArrayFactory::MakeClone<char>(choiceSel, typeSel, sizeSel), sortSel, benchOrSort);

		cout << endl;
	}
	// Syntax for parameters is (Ordering of Array, data type of array, size of array)
	//auto* arrMain = ArrayFactory::MakeClone<int>(3, 1, 10);
	//arrMain->DisplayArray();
	//arrMain->Benchmark("QuickSort");
	////arrMain->DisplayArray();
	//cout << endl;

	/*arr = ArrayFactor
	y::MakeClone<float>(2, 2, 10);
	arr->DisplayArray();
	cout << endl;

	arr = ArrayFactory::MakeClone<double>(3, 3, 10);
	arr->DisplayArray();
	cout << endl;

	arr = ArrayFactory::MakeClone<char>(4, 4, 10);
	arr->DisplayArray();
	cout << endl;*/
	//auto* arr = ArrayFactory::CreateArray<int>(1, 10);
	//arr->DisplayArray();
	/*auto* arr = ReverseArray<double>(10);
	DisplayArray(arr, 10);*/
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
