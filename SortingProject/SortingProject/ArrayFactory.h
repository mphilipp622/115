#pragma once
#include "Array.h"
#include "OrderedArray.h"
#include "RandomArray.h"
#include "ReverseArray.h"
#include "ShuffledArray.h"
#include <string>

using namespace std;

/*
This class is used for managing the prototypes in the project. It will basically create the prototypes
and allow us easy access to them.
*/
class ArrayFactory
{
public:
	ArrayFactory();
	~ArrayFactory();

	// Will create new prototypes
	template<typename T>
	static Array* CreateArray(int choice, int size)
	{
		if (choice == 1)
			return new OrderedArray<T>(size)->Clone();
		else if (choice == 2)
			return new ReverseArray<T>(size)->Clone();
		else if (choice == 3)
			return new RandomArray<T>(size)->Clone();
		else if (choice == 4)
			return new ShuffledArray<T>(size)->Clone();
	}
};

