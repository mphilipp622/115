// Project1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

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

void QuickSort(int* arr, int length)
{
	int pivot = (length - 1) / 2; // pivot will be in the middle of the array.
}

int main()
{
	srand(time(NULL));
	int *arr = randomArray(10);

	//SelectionSort(arr, 10);
	//BubbleSort(arr, 10);
	InsertionSort(arr, 10);
	DisplayArray(arr, 10);
	//BinarySearchIterative(arr, 10, 23);
	BinarySearchRecursive(arr, 0, 10, 23);

	return 0;
}

