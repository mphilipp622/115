#include <iostream>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "ArrayMaker.h"

using namespace std;
using namespace ArrayMaker;

//bool HasExceededTimeThreshold(chrono::time_point<chrono::system_clock> start, int time)
//{
//	/* time threshold will be set at 5 minutes total.
//	 If any algorithm runs longer than 5 minutes, than we will quit execution.*/
//	auto end = chrono::system_clock::now();
//	chrono::duration<double> elapsed = end - start;
//
//	if (elapsed.count() >= time)
//		return true;
//
//	return false;
//}

namespace Sorter
{

	template<typename T>
	void SelectionSort(T* arr, int length)
	{
		auto startTime = chrono::system_clock::now();

		for (int i = 0; i < length - 1 && !HasExceededTimeThreshold(startTime, 300); i++)
		{
			T min = arr[i]; // min value always starts at element stored in current index
			T minIndex = i; // set minimum index

			for (int j = i; j < length && !HasExceededTimeThreshold(startTime, 300); j++)
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

		if (HasExceededTimeThreshold(startTime, 300))
			cout << "SelectionSort" << length << " Has exceeded 5 minutes" << endl;
	}

	template<typename T>
	void BubbleSort(T* arr, int length)
	{
		bool swap = false; // flag for exit condition
		auto startTime = chrono::system_clock::now();
		chrono::duration<double> elapsedTotal; // will keep track of time.

		do
		{
			swap = false; // set flag to false every time

			for (int i = 0; i < length - 1 && !HasExceededTimeThreshold(startTime, 300); i++)
			{
				// iterate through the list as many times as it takes to sort. 
				if (arr[i + 1] < arr[i])
				{
					// perform a swap
					Swap(arr, i, i + 1);
					swap = true;
				}
			}
		} while (swap && !HasExceededTimeThreshold(startTime, 300)); // exit condition

		if (HasExceededTimeThreshold(startTime, 300))
			cout << "BubbleSort" << length << " Has exceeded 5 minutes" << endl;
	}

	template<typename T>
	void InsertionSort(T* arr, int length)
	{
		auto startTime = chrono::system_clock::now();

		for (int i = 0; i < length && !HasExceededTimeThreshold(startTime, 300); i++)
		{
			int index = i;

			while (arr[index - 1] > arr[index] && !HasExceededTimeThreshold(startTime, 300))
			{
				Swap(arr, index - 1, index);
				index = index - 1;
			}

		}

		if (HasExceededTimeThreshold(startTime, 300))
			cout << "InsertionSort" << length << " Has exceeded 5 minutes" << endl;
	}

	template<typename T>
	void Merge(T* arr, int left, int mid, int right)
	{
		int i, j, k;
		T *temp = new T[right - left + 1];
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


		// Assign sorted data stored in temp[] to arr[].
		for (i = left; i <= right; i++)
		{
			arr[i] = temp[i - left];
		}

		delete temp; // free memory to avoid overflows
	}

	template<typename T>
	void MergeSort(T* arr, int left, int right)
	{
		if (left < right)
		{
			int mid = (left + right) / 2;
			MergeSort(arr, left, mid);
			MergeSort(arr, mid + 1, right);
			Merge(arr, left, mid, right);
		}
	}

	template<typename T>
	int Partition(T* arr, int first, int last)
	{
		T pivot = arr[first + (last - first) / 2]; // get middle pivot
		int leftI = first - 1; // set left and right indexes
		int rightI = last + 1;
		while (leftI <= rightI)
		{
			while (arr[++leftI] < pivot); // loop until we find a value greater than pivot on the left
			while (arr[--rightI] > pivot); // loop until we find a value less than pivot on the right
			if (leftI >= rightI)break; // if the indexes have crossed, then we want to terminate
			Swap(arr, leftI, rightI); // swap the indexes
		}

		return rightI; // return the right index
	}

	template<typename T>
	void QuickSort(T* arr, int first, int last)
	{
		if (first < last)
		{
			int pivot = Partition(arr, first, last); // return q and update A
			QuickSort(arr, first, pivot); // apply on the first part of A (all the elements<A[q])
			QuickSort(arr, pivot + 1, last); // apply on the second part of A (all the elements>A[q])
		}
	}
}