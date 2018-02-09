#include "stdafx.h"
#include "Array.h"
#include <iostream>

using namespace std;

Array::Array()
{

}

Array::Array(int newSize)
{
	size = newSize;
	arrData = (int*)malloc(sizeof(int) * size);
	//arrData = new int[size];
}

Array::~Array()
{
	delete arrData;
}

void Array::InsertData()
{
	for (int i = 0; i < size; i++)
		arrData[i] = i;
}

void Array::DisplayData()
{
	for (int i = 0; i < size; i++)
		cout << arrData[i] << endl;
}

void Array::DeleteTop()
{
	for (int i = 0; i < size - 1; i++)
	{
		int temp = arrData[i + 1];
		arrData[i] = temp;
	}
}

void Array::SumOfOdds()
{
	int sum = 0;

	for (int i = 0; i < size; i++)
		arrData[i] % 2 == 1 ? sum += arrData[i] : sum += 0; // odd numbers divided by 2 have remainder of 1

	cout << "Sum of Odd elements: " << sum << endl;
}


void Array::ReverseArray()
{
	for (int i = 0; i < size / 2; i++)
	{
		// start from beginning and end and swap values until i meets in the middle
		int temp = arrData[(size-1) - i];
		arrData[(size - 1) - i] = arrData[i];
		arrData[i] = temp;
	}
}

void Array::AddToTop(int value)
{
	size = size++;

	arrData = (int*)realloc(arrData, sizeof(int)*size);

	for (int i = size - 1; i > 0; i--)
	{
		arrData[i] = arrData[i - 1];
		arrData[0] = value;
	}
}

