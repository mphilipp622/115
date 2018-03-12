/*
Mark Philipp
Isaac Fielding
CSCI 115
*/

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
Everything is static so the functions can be called without instantiation of the class in main. This also allows
the memory addresses for the original Arrays to persist throughout execution, which allows the clones to work properly
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
		int tempKey = (choice + type + size) * choice; // Hash key for the unordered_map

		// If the item does not exist in our map, then we will create it.
		// Choice dictates which kind of sorted array we instantiate
		if (choice == 1)
			arrays<T>[tempKey] = new ArrayTemplate::OrderedArray<T>(size, choice, type);
		else if (choice == 2)
			arrays<T>[tempKey] = new ArrayTemplate::ReverseArray<T>(size, choice, type);
		else if (choice == 3)
			arrays<T>[tempKey] = new ArrayTemplate::RandomArray<T>(size, choice, type);
		else if (choice == 4)
			arrays<T>[tempKey] = new ArrayTemplate::ShuffledArray<T>(size, choice, type);
	}

	// Will create a clone of the array that's chosen by the user
	template<typename T>
	static Array<T>* MakeClone(int choice, int type, int size)
	{
		int tempKey = (choice + type + size) * choice; // Create a hash key for the unordered_map

		if (!arrays<T>[tempKey])
			// if the item doesn't exist yet, create it.
			CreateArray<T>(choice, type, size);

		return arrays<T>[tempKey]->Clone(); // return a clone of the array
	}
private:
	/* 
	the map contains lookups for the different arrays that have been created.
	The key will be an int, which will be (<choice> + <arraySize> + <type>) * choice . This will ensure unique keys
	The choice represents Ordered, Reverse, Random, or Shuffle. The type represents an integer value that corresponds to a type

	type:
	1 = int
	2 = float
	3 = double
	4 = char

	choice:
	1 = Ordered Array
	2 = Reverse Array
	3 = Random Array
	4 = Shuffled Array
	*/
	template<typename T>
	static unordered_map<int, Array<T>*> arrays;
};

// Compiler wouldn't let me initialize the map in the class declaration because it's a static template variable.
// Did it here instead
template<typename T>
unordered_map<int, Array<T>*> ArrayFactory::arrays = {};