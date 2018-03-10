#pragma once
#include "stdafx.h"
#include <string>
#include <typeinfo>

using namespace std;

template<typename key, typename value>
class HashTable
{
public:
	HashTable()
	{
	}

	HashTable(int newSize)
	{
		size = newSize;
		numberOfRecords = 0;
		dictionary = new Lookup[size];
	}

	~HashTable() 
	{
		delete[] dictionary;
	}

	int GetSize()
	{
		return this->size;
	}

	bool IsEmpty()
	{
		return numberOfRecords > 0;
	}

	void Add(key newKey, value newValue)
	{
		Lookup temp(newKey, newValue);

		if (Contains(temp.thisKey))
		{
			cout << "Table already contains Key (" << newKey << ", " << newValue << ")" << endl;
			return;
		}

		int newIndex = CreateIndex(newKey);

		if (newIndex == -1)
			cout << "Cannot Add New Data. Table is Full" << endl;

		temp.isHashed = true;
		dictionary[newIndex].SetData(newKey, newValue);
		numberOfRecords++;
	}

	value GetValue(key keyToGet)
	{
		int index = FindIndex(keyToGet);
		if (index == -1)
		{
			cout << "Error: Table does not contain key '" << keyToGet << "'" << endl;
			return 0;
		}

		return dictionary[index].thisValue;
	}

	void SetValue(key keyToSet, value newValue)
	{
		int index = FindIndex(keyToGet);
		if (index == -1)
		{
			cout << "Error: Table does not contain key '" << keyToSet << "'" << endl;
			return;
		}

		dictionary[index].thisValue = newValue;
	}
	
	bool Contains(key keyToFind)
	{
		int index = FindIndex(keyToFind);

		if (index != -1) // we know that we don't have the key if we return -1
			return true;
		else
			return false;
	}
	/*void Remove(key) {};
	void Clear()
	{};*/


private:
	typedef struct Lookup
	{
		public:
			Lookup()
			{
				isHashed = false;
				/*if (typeid(key) == typeid(string) || typeid(key) == typeid(char*))
					thisKey = "";
				else
					thisKey = (key)0;

				thisValue = 0;*/
			}

			Lookup(key newKey, value newValue)
			{
				thisKey = newKey;
				thisValue = newValue;
				isHashed = false;
			}

			void SetData(key newKey, value newValue)
			{
				thisKey = newKey;
				thisValue = newValue;
				isHashed = true;
			}
			key thisKey;
			value thisValue;
			bool isHashed;
	};

	int size;
	int numberOfRecords;
	Lookup* dictionary;

	// Create a hashable index based on the key that's passed
	int CreateIndex(key newKey)
	{
		int index = 0;
		if (typeid(key) == typeid(string)) 
		{
			// if our key type is string, we need different behavior.
			//string temp = newKey;

			for (int i = 0; i < newKey.length(); i++)
				index += newKey.at(i);

			index %= size;
		}
		else if (typeid(key) == typeid(char*))
		{
			// if key type is char*, use different behavior
			for (int i = 0; i < sizeof(newKey) / sizeof(newKey[0]); i++)
				index += newKey[i];

			index %= size;

		}
		//else
		//{
		//	// otherwise, if key type is a decimal value or a char, use default behavior
		//	newKey % size;
		//}

		// check collision
		if (dictionary[index].isHashed)
		{
			for (int i = index; i < size; i++)
			{
				// iterate forward, looking for empty space
				if (!dictionary[i].isHashed)
				{
					// found empty spot
					index = i;
					return index;
				}
			}
			for (int i = index; i > -1; i--)
			{
				// iterate backwards, looking for empty space
				if (!dictionary[i].isHashed)
				{
					// found empty spot
					index = i;
					return index;
				}
			}
		}

		return -1; // -1 will be flag for knowing we are out of space in table
	}

	int FindIndex(key keyToFind)
	{
		int index = 0;

		if (typeid(key) == typeid(char*))
		{
			// if key type is char*, use different behavior
			for (int i = 0; i < sizeof(keyToFind) / sizeof(keyToFind[0]); i++)
				index += keyToFind[i];

			index %= size;

		}
		else if (typeid(key) == typeid(string))
		{
			string temp = keyToFind;

			for (int i = 0; i < temp.length(); i++)
				index += temp.at(i);

			index %= size;
		}
		//else
		//	// otherwise, if key type is a decimal value or a char, use default behavior
		//	keyToFind % size;

		// if we find the key immediately, return the index
		if (dictionary[index].thisKey == keyToFind)
			return index;

		// if we don't find key immediately, look for it
		for (int i = index; i < size; i++)
		{
			// iterate forward, looking for key
			if (dictionary[i].isHashed)
			{
				if (dictionary[i].thisKey == keyToFind)
				{
					index = i;
					return index;
				}
			}
		}
		for (int i = index; i > -1; i--)
		{
			// iterate backwards, looking for key
			if (dictionary[i].isHashed)
			{
				if (dictionary[i].thisKey == keyToFind)
				{
					index = i;
					return index;
				}
			}
		}

		return -1; // -1 will be flag for knowing we have no key
	}
};

