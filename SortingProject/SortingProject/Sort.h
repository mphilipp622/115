/*
Mark Philipp
CSCI 115
ID: 109941708
*/

#pragma once
#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "Array.h"
#include "Timer.h"

using namespace std;
using namespace Timer;

// Create a namespace for easy usage in the rest of the program. Namespace has no member variables, only functions.
namespace Sort
{

	// Sorts arr using Selection Sort
	template<typename T>
	void SelectionSort(T* arr, int length)
	{
		auto startTime = chrono::system_clock::now(); // Timer will check if we've exceeded max time threshold

		for (int i = 0; i < length - 1 && !HasExceededTimeThreshold(startTime, 300); i++)
		{
			T min = arr[i]; // min value always starts at element stored in current index
			int minIndex = i; // set minimum index

			for (int j = i; j < length + 1 && !HasExceededTimeThreshold(startTime, 300); j++)
			{
				if (arr[j] < min)
				{
					// if current element is less than previously minimum element, change min and set minindex
					min = arr[j];
					minIndex = j;
				}
			}

			if (min < arr[i]) // if min value is < the current index of the array, swap
				Swap<T>(arr, minIndex, i);
		}

		if (HasExceededTimeThreshold(startTime, 300))
			cout << "SelectionSort" << length << " Has exceeded 5 minutes" << endl;
	}

	// Sorts arr using Bubble Sort
	template<typename T>
	void BubbleSort(T* arr, int length)
	{
		bool swap = false; // flag for exit condition

		auto startTime = chrono::system_clock::now(); // Timer will check if we've exceeded max time threshold

		do
		{
			swap = false; // set flag to false every time

			for (int i = 0; i < length - 1 && !HasExceededTimeThreshold(startTime, 300); i++)
			{
				// iterate through the list as many times as it takes to sort. 
				if (arr[i + 1] < arr[i])
				{
					// perform a swap
					Swap<T>(arr, i, i + 1);
					swap = true;
				}
			}
		} while (swap && !HasExceededTimeThreshold(startTime, 300)); // exit condition

		
		if (HasExceededTimeThreshold(startTime, 300))
			cout << "BubbleSort" << length << " Has exceeded 5 minutes" << endl;
	}

	// Sorts arr using Insertion Sort
	template<typename T>
	void InsertionSort(T* arr, int length)
	{
		auto startTime = chrono::system_clock::now(); // Timer will check if we've exceeded max time threshold

		for (int i = 1; i < length && !HasExceededTimeThreshold(startTime, 300); i++)
		{
			int index = i; // get current index

			while (arr[index - 1] > arr[index] && !HasExceededTimeThreshold(startTime, 300))
			{
				// check the outer loop's index - 1 and compare it to out loop's current index. Swap if current is < previous
				Swap<T>(arr, index - 1, index);
				index = index - 1; // reset index to the lower value
			}

		}

		if (HasExceededTimeThreshold(startTime, 300))
			cout << "InsertionSort" << length << " Has exceeded 5 minutes" << endl;
	}

	// Used by Merge Sort for merging two arrays together and sorting them
	template<typename T>
	void Merge(T* arr, int left, int mid, int right)
	{
		int i, j, k;
		T *temp = new T[right - left + 1]; // temp array where merging will happen
		i = left; // starts at front of array
		k = 0; // will be current index of the temp array
		j = mid + 1; // starts halfway through array

		// Merge the two parts into temp[].
		while (i <= mid && j <= right)
		{
			// compare the elements on one half of the array with the other half
			if (arr[i] < arr[j])
			{
				temp[k] = arr[i]; // assign the smaller value into the kth index of temp
				k++; // move k forward
				i++; // move i forward
			}
			else
			{
				temp[k] = arr[j]; // assign the smaller index at j into kth index of temp
				k++; // move k forward
				j++; // move j forward
			}
		}

		// Insert all the remaining values from i to mid into temp[]. This only happens if we didn't reach the end of left-half
		while (i <= mid)
		{
			temp[k] = arr[i];
			k++;
			i++;
		}

		// Insert all the remaining values from j to high into temp[]. Only happens if we didn't reach end of right-half
		while (j <= right)
		{
			temp[k] = arr[j];
			k++;
			j++;
		}


		// Assign sorted data stored in temp[] to arr[].
		for (i = left; i <= right; i++)
		{
			arr[i] = temp[i - left];
		}

		delete temp; // free memory to avoid overflows
	}

	// Sorts arr using Merge Sort
	template<typename T>
	void MergeSort(T* arr, int left, int right)
	{
		if (left < right)
		{
			int mid = (left + right) / 2; // get middle index
			MergeSort<T>(arr, left, mid); // recurse on left-half
			MergeSort<T>(arr, mid + 1, right); // recurse on right-half
			Merge<T>(arr, left, mid, right); // merge the data
		}
	}

	// Used to get index for Quick Sort
	template<typename T>
	int Partition(T* arr, int first, int last)
	{
		T pivot = arr[first + (last - first) / 2]; // get middle pivot
		
		// set left and right indexes
		int leftI = first - 1; 
		int rightI = last + 1;

		while (leftI <= rightI)
		{
			// these while loops will ensure we pause execution until we find a value on the left and right that meet their criteria
			while (arr[++leftI] < pivot); // loop until we find a value greater than pivot on the left
			while (arr[--rightI] > pivot); // loop until we find a value less than pivot on the right

			if (leftI >= rightI)
				break; // if the indexes have crossed, then we want to terminate

			Swap<T>(arr, leftI, rightI); // swap the indexes
		}

		return rightI; // return the right index since it should be the max index we care about now
	}

	// Sorts arr using Quick Sort
	template<typename T>
	void QuickSort(T* arr, int first, int last)
	{
		if (first < last)
		{
			int pivot = Partition(arr, first, last); // return needed index and update arr
			QuickSort<T>(arr, first, pivot); // apply on the first part of arr (all the elements < arr[pivot])
			QuickSort<T>(arr, pivot + 1, last); // apply on the second part of arr (all the elements > arr[pivot])
		}
	}

	// Used for Swapping elements in the array.
	template<typename T>
	void Swap(T* arr, int i, int j)
	{
		T temp;
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
};