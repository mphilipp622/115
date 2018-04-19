#include "Grid.h"

Grid::Grid(int newXSize, int newYSize, vector<vector<int>> map)
{
	sizeX = newXSize;
	sizeY = newYSize;

	for(int i = 0; i < sizeX; i++)
    {
        tiles.push_back(vector<Tile*>());
    }

    // GRID COORDINATES START FROM BOTTOM LEFT.
    // Origin at bottom left is (0, 0). Top right is (sizeX, sizeY)
	for (int i = 0; i < sizeY; i++)
	{
//		tiles.push_back(vector<Tile*>()); // create new row
		for (int j = 0; j < sizeX; j++)
        {
			tiles[j].push_back(new Tile(j, i, 1.0, 1.0, static_cast<Type>(map.at(sizeY - i - 1).at(j)))); // create a new tile at (i, j) position

			if(map.at(sizeY - i - 1).at(j) == Type::player)
                // create player
                player = new Player(j, i);
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

Player* Grid::GetPlayer()
{
    return player;
}

int Grid::GetSizeX()
{
    return sizeX;
}

int Grid::GetSizeY()
{
    return sizeY;
}
