#include "stdafx.h"
#include "Sorter.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

namespace Sorter
{
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
		if (first < last)
		{
			int pivot = Partition(arr, first, last); // return q and update A
			QuickSort(arr, first, pivot - 1); // apply on the first part of A (all the elements<A[q])
			QuickSort(arr, pivot + 1, last); // apply on the second part of A (all the elements>A[q])
		}
	}

	int* RandomArray(int length)
	{
		//srand(time(NULL));
		int *arr = new int[length];

		for (int i = 0; i < length; i++)
			arr[i] = rand() % (length * 5);

		return arr;
	}

	int* ReverseArray(int length)
	{
		int* arr = new int[length];

		for (int i = 0, j = length; i < length; i++, j--)
			arr[i] = j; // created sorted array

		return arr;
	}

	int* OrderedArray(int length)
	{
		int* arr = new int[length];

		for (int i = 0; i < length; i++)
			arr[i] = i; // created sorted array


		return arr;
	}

	int* ShuffleTen(int length)
	{
		//srand(time(NULL));

		int* arr = new int[length];

		int cap = length * 0.1; // 10% of the length

		for (int i = 0; i < length; i++)
			// Initialize an ordered array first.
			arr[i] = i;

		for (int i = 0; i < cap; i++)
		{
			// shuffle 10% of the array
			int randIndex = rand() % length;
			Swap(arr, i, randIndex);
		}

		return arr;
	}
}