#pragma once

// Custom namespace that includes all the necessary sorting functions
namespace Sorter
{
	// outputs contents of array to console
	void DisplayArray(int* arr, int length);

	// swaps two elements in an array
	void Swap(int* arr, int element1, int element2);

	// Sort array using Selection Sort
	void SelectionSort(int* arr, int length);

	// Sort array using Bubble Sort
	void BubbleSort(int* arr, int length);

	// Sort array using InsertionSort
	void InsertionSort(int* arr, int length);

	// Merge functionality for MergeSort
	void Merge(int* arr, int left, int mid, int right);

	// Sorts array using Merge Sort. Be sure to pass size - 1 as "last" parameter
	void MergeSort(int* arr, int left, int right);

	// Calculates partition for Quick Sort
	int Partition(int* arr, int first, int last);

	// Sorts array using Quick Sort. Be sure to pass size - 1 as "last" parameter
	void QuickSort(int* arr, int first, int last);

	// Creates a random array of the specified size
	int* RandomArray(int length);

}