// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
	Array A(20);

	A.InsertData();
	A.DisplayData();

	cout << endl;

	A.SumOfOdds();

	cout << endl;

	A.ReverseArray();
	A.DeleteTop();
	A.AddToTop(5555);
	A.DisplayData();

    return 0;
}

