/*
Mark Philipp
Isaac Fielding
CSCI 115
*/

#include "stdafx.h"
#include <iostream>
#include "ArrayFactory.h"

using namespace std;

// Will provide output to the user based on the values they selected.
// This implementation was the best way I could find to make my code work with the templated Array class.
template<typename T>
void ExecuteUserCommands(Array<T>* arr, int sortSel, int benchOrSort)
{
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

	delete arr;
}

int main()
{
	// choiceSel = the initial sorting order of the array. Ordered, Reverse, Shuffled, Random
	// typeSel = the data type of the array: int, float, double, char
	// sizeSel = size of array. sizeSel > 0 && sizeSel <= 1000000
	// sortSel = sorting method to use: Bubble, Selection, Insertion, Quick, Merge
	// benchOrSort = Sort data or benchmark the data.
	int choiceSel = 0 , typeSel = 0, sizeSel = 0, sortSel = 0, benchOrSort = 0;

	while (!cin.eof())
	{
		while (true)
		{
			// user selects the sorting algorithm to use

			cout << "Select a sorting algorithm" << endl;
			cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n0. Exit" << endl;
			cin >> sortSel;
			cout << endl;

			if (sortSel == 0)
				return 0;

			if (sortSel < 0 || sortSel > 5)
				cout << "ERROR: input must be 1, 2, 3, 4, 5, or 0" << endl; // invalid input check
			else
				break;
		}

		while (true)
		{
			// user selects data type for array

			cout << "Select a data type" << endl;
			cout << "1. int\n2. float\n3. double\n4. char\n0. Exit" << endl;
			cin >> typeSel;
			cout << endl;

			if (typeSel == 0)
				return 0;

			if (typeSel < 0 || typeSel > 4)
				cout << "ERROR: input must be 1, 2, 3 or 4" << endl; // invalid input check
			else
				break;
			
			cout << endl;
		}

		while (true)
		{
			// user inputs array size

			cout << "Enter an array size (0 to exit. Size must be positive and less than or equal to 1000000)" << endl;
			cin >> sizeSel;
			cout << endl;

			if (sizeSel == 0)
				return 0;

			if (sizeSel < 0 || sizeSel > 1000000)
				cout << "Error: Size must be a positive value and less than 1000000" << endl; // check for invalid input
			else
				break;

			cout << endl;
		}

		while (true)
		{
			// user selects the initial sorting of the array

			cout << "Choose the Initial Sorting" << endl;
			cout << "1. Ordered Array\n2. ReverseArray\n3. Random Array\n4. Shuffled Array (10%)\n0. Exit" << endl;
			cin >> choiceSel;
			cout << endl;

			if (choiceSel == 0)
				return 0;

			if (choiceSel < 0 || choiceSel > 4)
				cout << "ERROR: Input must be 1, 2, 3, 4 or 0" << endl; // invalid input check
			else
				break;
			
			cout << endl;
		}

		while (true)
		{
			// user selects if they want to simply sort or perform a benchmark

			cout << "Choose What Action to Perform" << endl;
			cout << "1. Sort and Display Results\n2. Benchmark and Display Time\n0. Exit" << endl;
			cin >> benchOrSort;
			cout << endl;

			if (benchOrSort == 0)
				return 0;

			if (benchOrSort < 0 || benchOrSort > 2)
				cout << "ERROR: Selection must be 1, 2, or 0" << endl; // invalid input check
			else
				break;
			
			cout << endl;
		}

		// Execute user selections. Have to pass different types for MakeClone based on selection
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

	return 0;
}
