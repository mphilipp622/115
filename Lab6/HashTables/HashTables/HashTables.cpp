
#include "stdafx.h"
#include <iostream>
#include <string>
#include <typeinfo>
#include "HashTable.h"

using namespace std;

int main()
{

	HashTable<string, int> myTable(10);
	string temp = "abc";

	myTable.Add(temp, 10);
	//myTable.Add(temp, 10);
	/*myTable.Add("abc", 5);
	myTable.Add('b', 7);

	cout << myTable.GetValue("abc") << endl;*/
	//cout << myTable.GetValue('b') << endl;

    return 0;
}