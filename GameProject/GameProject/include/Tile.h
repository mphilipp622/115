#ifndef TILE_H
#define TILE_H
#include "Type.h"
#include <Model.h>

/*
Class for tiles in the maze. This is useful for tracking the type of the tile. Also useful for
knowing if enemeis and players have moved onto or off of a tile. Also useful for creating a 2D vector in
the Grid class for easily accessing the tiles of the maze.
*/
class Tile : public Model
{
public:
	Tile(int newX, int newY, double newWidth, double newHeight, Type newType);
	~Tile();

	// Returns type of this tile
	int GetType();

	// Sets The type of the tile
	void SetType(Type newType);

	void RevertType();

	void RemoveArrows();

	// Returns true if tile is traversible
	bool IsTraversable();

	// Returns true if tile is a wall
	bool IsWall();

	// Returns true if tile contains an enemy
	bool IsEnemy();

	// Returns true if tile contains treasure
	bool IsTreasure();

	// Returns true if tile has arrows
	bool IsArrows();

	// returns true if tile has player
	bool IsPlayer();

private:
	Type tileType;
	Type originalType;

};


#endif // TILE_H
