// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int factWithFor(int n);
int factWithWhile(int n);
int fact(int n);

int fibFor(int n);
int fibWhile(int n);
int fib(int n);

void HanoiRec(int discs, int poles);

int main()
{
	/*cout << factWithFor(6) << endl;
	cout << factWithWhile(6) << endl;
	cout << fact(6) << endl;*/
	cout << fibFor(7) << endl;
	cout << fibWhile(7) << endl;
	cout << fib(7) << endl;
    return 0;
}

int factWithFor(int n)
{
	int fact = n;

	for (int i = n; i > 1; i--)
	{
		fact = fact * (i - 1);
	}

	return fact;
}

int factWithWhile(int n)
{
	int fact = n;

	while (n > 1)
	{
		fact = fact * (n - 1);
		n--;
	}

	return fact;
}

int fact(int n)
{
	if (n == 1) return 1;

	return n * fact(n - 1);
}

int fibFor(int n)
{
	int fib = 2, fib1 = 1, fib2 = 1;

	if (n < 2) return n;

	for (int i = 3; i < n; i++)
	{
		fib2 = fib1;
		fib1 = fib;

		fib = fib1 + fib2;
	}

	return fib;
}

int fibWhile(int n)
{
	int fib = 2, fib1 = 1, fib2 = 1;
	int counter = 3;

	if (n < 2) return n;

	while (counter < n)
	{

		fib2 = fib1;
		fib1 = fib;

		fib = fib1 + fib2;
		counter++;
	}

	return fib;
}

int fib(int n)
{
	if (n < 2) return n;
	return fib(n - 1) + fib(n - 2);
}

void HanoiRec(int n, int A, int B, int C)
{
	if (n > 0)
	{
		HanoiRec(n - 1, A, C, B);
		cout << "Move Disk From " << A << " to " << C << endl;
		HanoiRec(n - 1, B, A, C);
	}
}