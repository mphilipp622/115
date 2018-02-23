#pragma once
#include "Array.h"
#include "OrderedArray.h"
#include "RandomArray.h"
#include "ReverseArray.h"
#include "ShuffledArray.h"
#include <string>
#include <unordered_map>

using namespace std;

/*
This class is used for managing the prototypes in the project. It will basically create the prototypes
and allow us easy access to them.

There was some difficulty getting this to work well with templates. I had to make some of my own adaptations.
*/
class ArrayFactory
{
public:
	ArrayFactory();

	~ArrayFactory();

	// Will create new prototypes
	template<typename T>
	static void CreateArray(int choice, int type, int size)
	{
		int tempKey = (choice + type + size) * choice;

		auto finder = arrays.find(tempKey);

		if (finder == arrays.end())
		{
			// If the item does not exist in our map, then we will create it.
			if (choice == 1)
				arrays[tempKey] = new ArrayTemplate::OrderedArray<T>(size);
			else if (choice == 2)
				arrays[tempKey] = new ArrayTemplate::ReverseArray<T>(size);
			else if (choice == 3)
				arrays[tempKey] = new ArrayTemplate::RandomArray<T>(size);
			else if (choice == 4)
				arrays[tempKey] = new ArrayTemplate::ShuffledArray<T>(size);
		}

	}

	template<typename T>
	static Array* MakeClone(int choice, int type, int size)
	{
		int tempKey = (choice + type + size) * choice;

		auto finder = arrays.find(tempKey);

		if (finder == arrays.end())
			// if the item doesn't exist yet, create it.
			CreateArray<T>(choice, type, size);

		return arrays[tempKey]->Clone();
	}
private:
	// the map contains lookups for the different arrays that have been created.
	// The key will be an int, which will be (<choice> + <arraySize> + <type>) * choice . This will ensure unique keys
	// The choice represents Ordered, Reverse, Random, or Shuffle. The type represents an integer value that corresponds to a type

	// 1 = int
	// 2 = float
	// 3 = double
	// 4 = char

	// 1 = Ordered Array
	// 2 = Reverse Array
	// 3 = Random Array
	// 4 = Shuffled Array
	static unordered_map<int, Array*> arrays;
};

unordered_map<int, Array*> ArrayFactory::arrays = {};