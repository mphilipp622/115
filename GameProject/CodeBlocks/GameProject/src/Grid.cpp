#include "Grid.h"

Grid::Grid(int newXSize, int newYSize, vector<vector<int>> map)
{
	sizeX = newXSize;
	sizeY = newYSize;

	for (int i = 0; i < sizeX; i++)
	{
		tiles.push_back(vector<Tile*>()); // create new row

		for (int j = 0; j < sizeY; j++)
        {
			tiles[i].push_back(new Tile(j, i, 1.0, 1.0, static_cast<Type>(map.at(i).at(j)))); // create a new tile at (i, j) position
//			cout << "Tile Created at: " << j << "    " << i << endl;
        }
	}

}

Grid::~Grid()
{
}

Tile * Grid::GetTile(int xPos, int yPos)
{
	return tiles[xPos][yPos];
}

vector<vector<Tile*>> &Grid::GetTiles()
{
    return tiles;
}
