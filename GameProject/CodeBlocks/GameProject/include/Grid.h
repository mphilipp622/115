#ifndef GRID_H
#define GRID_H
#include "Type.h"
#include "Tile.h"

#include <vector>

using namespace std;

class Grid
{
public:
	Grid(int newXSize, int newYSize, vector<vector<int>> map);
	~Grid();

	Tile* GetTile(int xPos, int yPos);

private:
	int sizeX, sizeY;

	// 2-d grid of tiles
	vector<vector<Tile*>> tiles;
};


#endif // GRID_H
