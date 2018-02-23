#pragma once
#include <iostream>

// Base class for all array types. Implements Prototype pattern
class Array
{
public:
	Array();
	~Array();
	virtual Array* Clone() = 0; // prototype pattern
	int GetSize()
	{
		return this->size;
	}
	virtual void DisplayArray();
protected:
	int size;
	
};
