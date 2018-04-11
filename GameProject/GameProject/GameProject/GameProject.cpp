// GameProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int gridSizeX = 0, gridSizeY = 0;
	string mapFilePath = "";

	cout << "Input Grid's X Size: ";
	while (gridSizeX <= 0)
	{
		cin >> gridSizeX;

		if (gridSizeX <= 0)
			cout << "Invalid input. Input X Value Larger Than 0: ";
	}

	cout << "Input Grid's Y Size: ";
	while (gridSizeY <= 0)
	{
		cin >> gridSizeY;

		if (gridSizeY <= 0)
			cout << "Invalid Input. Input Y Value Larger Than 0: ";
	}

	cout << "Input Filepath for Grid Layout: ";
	while (mapFilePath.empty())
	{
		getline(cin, mapFilePath);
	}

	cout << gridSizeX << ", " << gridSizeY << "    " << mapFilePath << endl;

    return 0;
}

