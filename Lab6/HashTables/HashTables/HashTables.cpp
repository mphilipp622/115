
#include "stdafx.h"
#include <iostream>
#include <string>
#include <typeinfo>
#include "HashTable.h"

using namespace std;

int main()
{
	HashTable<char, int> myTable(10);

	myTable.Add('a', 5);
	myTable.Add('b', 7);

	cout << myTable.GetValue('a') << endl;
	cout << myTable.GetValue('b') << endl;

    return 0;
}