#pragma once

namespace Sorter
{
	// outputs contents of array to console
	static void DisplayArray();

	// swaps two elements in an array
	static void Swap(int* arr, int element1, int element2);

	// Sort array using Selection Sort
	static void SelectionSort(int* arr, int length);

	// Sort array using Bubble Sort
	static void BubbleSort(int* arr, int length);

	// Sort array using InsertionSort
	static void InsertionSort(int* arr, int length);

	// Merge functionality for MergeSort
	static void Merge(int* arr, int left, int mid, int right);

	// Sorts array using Merge Sort
	static void MergeSort(int* arr, int left, int right);

	// Calculates partition for Quick Sort
	static int Partition(int* arr, int first, int last);

	// Sorts array using Quick Sort
	static void QuickSort(int* arr, int first, int last);

};