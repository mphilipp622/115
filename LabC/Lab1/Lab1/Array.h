#pragma once

class Array
{
public:
	Array();
	Array(int);
	~Array();

	// Populate array with default data.
	void InsertData();

	// Outputs the contents of the array to the command line
	void DisplayData();

	// Removes the 0th element of the array. Moves all subsequent elements up by an index
	void DeleteTop();

	// take the sum of the odd elements of the array and display it
	void SumOfOdds();

	// reverse the elements of the array
	void ReverseArray();

	void AddToTop(int);

protected:
private:
	int size; // size of array
	int* arrData; // array data

};

