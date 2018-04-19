#ifndef TILE_H
#define TILE_H
#include "Type.h"
#include <Model.h>

class Tile : public Model
{
public:
	Tile(int newX, int newY, double newWidth, double newHeight, Type newType);
	~Tile();

	// Returns x position of this tile
	int GetX();

	// Returns y position of this tile
	int GetY();

	// Returns type of this tile
	int GetType();

	// Sets The type of the tile
	void SetType(Type newType);

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

private:
	int xPos, yPos;
	// Model* model;
	Type tileType;

};


#endif // TILE_H
