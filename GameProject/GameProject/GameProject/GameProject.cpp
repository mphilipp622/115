// GameProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>
#include "Grid.h"

using namespace std;

int main()
{
	int gridSizeX = 0, gridSizeY = 0;
	string mapFilePath = "";
	Grid* grid;
	string line;
	vector<vector<int>> gridMap;

	cout << "Input Filepath for Grid Layout: ";
	while (mapFilePath.empty())
	{
		getline(cin, mapFilePath);
	}

	ifstream in(mapFilePath);

	for (int i = 0; !in.eof(); i++)
	{
		getline(in, line); // read first row of data
		gridMap.push_back(vector<int>());
		gridSizeY = line.size();

		for (int j = 0; j < gridSizeY; j++)
			gridMap[i].push_back(line.at(j) - '0'); // convert from ascii to int

		gridSizeX = i + 1;
	}

	grid = new Grid(gridSizeX, gridSizeY, gridMap);
	
	for (int i = 0; i < gridSizeX; i++)
	{
		for (int j = 0; j < gridSizeY; j++)
			cout << grid->GetTile(i, j)->GetType();
		cout << endl;
	}

    return 0;
}

