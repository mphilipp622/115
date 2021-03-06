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
#include "Sorter.h"

using namespace std;

int* randomArray(int length)
{
	int *arr = new int[length];

	for (int i = 0; i < length; i++)
		arr[i] = rand() % 100;

	return arr;
}

int main()
{
	int size = 10;
	srand(time(NULL));
	int *arr = randomArray(size);
	auto start = chrono::system_clock::now();

	//SelectionSort(arr, 10);
	//BubbleSort(arr, 10);
	//InsertionSort(arr, 10);
	//DisplayArray(arr, size);
	cout << "Sorting" << endl;
	Sorter::QuickSort(arr, 0, size - 1);
	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	std::time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "Time Passed: " << elapsed.count() << endl;

	//MergeSort(arr, 0, size-1);

	return 0;
}
