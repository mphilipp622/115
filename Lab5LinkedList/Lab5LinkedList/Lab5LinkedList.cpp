// Lab5LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "List.h"
#include <iostream>
#include "Node.h"

using namespace std;

int main()
{
	List<int> intList;

	intList.InsertFront(15);
	intList.InsertBack(23);
	intList.Insert(1, 5);

	cout << intList.GetFront() << endl;
	cout << intList.GetBack() << endl;
	cout << intList.Get(0) << endl;

    return 0;
}

