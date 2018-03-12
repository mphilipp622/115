/*
Mark Philipp
Isaac Fielding
CSCI 115
*/

#pragma once
#include <iostream>

// Base class for all array types. Implements Prototype pattern. Implementation is in the header file so C++ linker
// can compile the templated class
template<typename T>
class Array
{
public:

	Array()
	{
	}
	~Array()
	{

	}

	// prototype pattern
	virtual Array<T>* Clone() = 0; 

	// returns the size of the array
	int GetSize()
	{
		return this->size;
	}

	// outputs contents of the array to the console
	virtual void DisplayArray() = 0;

	/*
	Keeps track of running time for sorting this array. Outputs running information to console and
	opens output files and writes time data to them so I can easily bring the data into Excel for analysis.
	*/
	virtual void Benchmark(std::string method) = 0;

	// Returns a pointer to the array data. Public getter
	virtual T* GetData() = 0;

protected:
	// These variables will be used in main for user input
	int size, choice, type;

private:
	T* arr; // array data
};