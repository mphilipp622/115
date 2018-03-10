#pragma once
#include "stdafx.h"
#include <string>
#include <typeinfo>

template<typename key, typename value>
class HashTable
{
public:
	HashTable();

	HashTable(int newSize)
	{
		size = newSize;
		numberOfRecords = 0;
		dictionary = new Lookup[size];
	}

	~HashTable();

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
			cout << "Cannot Add New Data. Table is Fulle" << endl;

		dictionary[newIndex] = temp;
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
	void Remove(key);
	void Clear();


private:
	struct Lookup
	{
		public:
			Lookup();
			Lookup(key newKey, value newValue)
			{
				thisKey = newKey;
				thisValue = newValue;
			}
			key thisKey;
			value thisValue;
	};

	int size;
	int numberOfRecords;
	Lookup* dictionary;

	// Create a hashable index based on the key that's passed
	int CreateIndex(key newKey)
	{
		int index = 0;

		if (typeid(newKey).name() == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") 
		{
			// if our key type is string, we need different behavior.
			string temp = newKey;

			for (int i = 0; i < temp.length(); i++)
				index += temp.at(i);

			index %= size;
		}
		else if (typeid(newKey).name() == "char const * __cdecl(void)")
		{
			// if key type is char*, use different behavior
			for (int i = 0; i < sizeof(newKey) / sizeof(newKey[0]); i++)
				index += newKey[i];

			index %= size;

		}
		else
		{
			// otherwise, if key type is a decimal value or a char, use default behavior
			newKey % size;
		}

		// check collision
		if (dictionary[index])
		{
			for (int i = index; i < size; i++)
			{
				// iterate forward, looking for empty space
				if (!dictionary[i])
				{
					// found empty spot
					index = i;
					return index;
				}
			}
			for (int i = index; i > -1; i--)
			{
				// iterate backwards, looking for empty space
				if (!dictionary[i])
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

		if (typeid(keyToFind).name() == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >")
		{
			// if our key type is string, we need different behavior.
			string temp = keyToFind;

			for (int i = 0; i < temp.length(); i++)
				index += temp.at(i);

			index %= size;
		}
		else if (typeid(keyToFind).name() == "char const * __cdecl(void)")
		{
			// if key type is char*, use different behavior
			for (int i = 0; i < sizeof(keyToFind) / sizeof(keyToFind[0]); i++)
				index += keyToFind[i];

			index %= size;

		}
		else
		{
			// otherwise, if key type is a decimal value or a char, use default behavior
			keyToFind % size;
		}

		// if we find the key immediately, return the index
		if (dictionary[index].thisKey == keyToFind)
			return index;

		// if we don't find key immediately, look for it
		for (int i = index; i < size; i++)
		{
			// iterate forward, looking for key
			if (dictionary[i])
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
			if (dictionary[i])
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

