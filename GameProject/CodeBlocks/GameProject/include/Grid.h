#ifndef GRID_H
#define GRID_H
#include "Type.h"
#include "Tile.h"

#include <vector>
#include <Player.h>

using namespace std;

class Grid
{
public:
	Grid(int newXSize, int newYSize, vector<vector<int>> map);
	~Grid();

	// Gets a single tile. Useful for detecting collisions and pathfinding
	Tile* GetTile(int xPos, int yPos);

	Player* GetPlayer();

	// returns the vector of tiles. Used by GLScene to draw tile models
	vector<vector<Tile*>> &GetTiles();

private:
	int sizeX, sizeY;

	// 2-d grid of tiles
	vector<vector<Tile*>> tiles;

	Player* player;
};


#endif // GRID_H
