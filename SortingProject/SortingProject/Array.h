#pragma once

// Base class for all array types. Implements Prototype pattern
class Array
{
public:
	Array();
	~Array();
	virtual Array* Clone() = 0; // prototype pattern
	int GetSize();
	void DisplayArray();
protected:
	int size;
private:

};

