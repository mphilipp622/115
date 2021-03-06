// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stack>
#include <time.h>
#include <chrono>
#include <ctime>

using namespace std;

int* randomArray(int length)
{
	int *arr = new int[length];

	for (int i = 0; i < length; i++)
		arr[i] = rand() % 100;

	return arr;
}

void DisplayArray(int* arr, int length)
{
	for (int i = 0; i < length; i++)
		cout << arr[i] << endl;
}

void Swap(int* arr, int i, int j)
{
	int temp;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void SelectionSort(int* arr, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		int min = arr[i]; // min value always starts at element stored in current index
		int minIndex = i; // set minimum index

		for (int j = i; j < length; j++)
		{
			if (arr[j] < min)
			{
				// if current element is less than previously minimum element, change min and set minindex
				min = arr[j];
				minIndex = j;
			}
		}

		if (min < arr[i]) // if min value is < the current index of the array, swap
			Swap(arr, minIndex, i);
	}
}

void BubbleSort(int* arr, int length)
{
	bool swap = false; // flag for exit condition

	do
	{
		swap = false; // set flag to false every time

		for (int i = 0; i < length - 1; i++)
		{
			// iterate through the list as many times as it takes to sort. 
			if (arr[i + 1] < arr[i])
			{
				// perform a swap
				Swap(arr, i, i + 1);
				swap = true;
			}
		}
	} while (swap); // exit condition
}

void InsertionSort(int* arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		int index = i;

		while (arr[index - 1] > arr[index])
		{
			Swap(arr, index - 1, index);
			index = index - 1;
		}

	}
}

void Merge(int* arr, int left, int mid, int right)
{
	int i, j, k;
	int *temp = new int[right - left + 1];
	i = left;
	k = 0;
	j = mid + 1;

	// Merge the two parts into temp[].
	while (i <= mid && j <= right)
	{
		if (arr[i] < arr[j])
		{
			temp[k] = arr[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = arr[j];
			k++;
			j++;
		}
	}

	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = arr[i];
		k++;
		i++;
	}

	// Insert all the remaining values from j to high into temp[].
	while (j <= right)
	{
		temp[k] = arr[j];
		k++;
		j++;
	}


	// Assign sorted data stored in temp[] to a[].
	for (i = left; i <= right; i++)
	{
		arr[i] = temp[i - left];
	}
}

void MergeSort(int* arr, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		Merge(arr, left, mid, right);
	}
}

int Partition(int* arr, int first, int last)
{
	int pivot = arr[last];
	
	int i = first - 1;

	for (int j = first; j < last; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			Swap(arr, i, j);
		}
	}

	Swap(arr, i + 1, last);
	return (i + 1);
}

void QuickSort(int* arr, int first, int last)
{
	if(first < last)
	{
		int pivot = Partition(arr, first, last); // return q and update A
		QuickSort(arr, first, pivot - 1); // apply on the first part of A (all the elements<A[q])
		QuickSort(arr, pivot + 1, last); // apply on the second part of A (all the elements>A[q])
	}
}

void BinarySearchIterative(int* arr, int length, int searchKey)
{
	int low = 0;
	int high = length - 1;
	int mid = high / 2;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (searchKey < arr[mid])
			high = mid - 1;
		else if (searchKey > arr[mid])
			low = mid + 1;
		else
		{
			cout << arr[mid] << " exists" << endl;
			return;
		}
	}
	cout << searchKey << " does not exist" << endl;
}

void BinarySearchRecursive(int* arr, int low, int high, int searchKey)
{

	int mid = ((low + high) / 2) - 1;

	if (arr[mid] == searchKey)
	{
		cout << searchKey << " exists" << endl;
		return;
	}
	else if (searchKey < arr[mid])
		BinarySearchRecursive(arr, low, mid, searchKey);
	else if (searchKey > arr[mid])
		BinarySearchRecursive(arr, mid, high, searchKey);
	else
		cout << searchKey << " does not exist" << endl;
}

int main()
{
	int size = 10;
	srand (time(NULL));
	int *arr = randomArray(size);
	auto start = chrono::system_clock::now();

	//SelectionSort(arr, 10);
	//BubbleSort(arr, 10);
	//InsertionSort(arr, 10);
	//DisplayArray(arr, size);
	cout << "Sorting" << endl;
	QuickSort(arr, 0, size-1);
	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	std::time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "Time Passed: " << elapsed.count() << endl;

	//MergeSort(arr, 0, size-1);

    return 0;
}
