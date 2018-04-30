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

	// Gets a single tile. Useful for detecting collisions and pathfinding
	Tile* GetTile(int xPos, int yPos);

	// returns the vector of tiles. Used by GLScene to draw tile models
	vector<vector<Tile*>> &GetTiles();

	// Getters for x and y dimensions of the grid
	int GetSizeX();
	int GetSizeY();

	// globally accessible instance of Grid. Used by Enemy, Player, and Projectile.
	static Grid* grid;

	// Checks x and y to see if they fall within grid boundaries. Returns FALSE if out of bounds
	bool BoundSafe(int x, int y);

private:
    // Private x and y dimensions of grid
	int sizeX, sizeY;

	// 2-d matrix of tiles
	vector<vector<Tile*>> tiles;
};


#endif // GRID_H
