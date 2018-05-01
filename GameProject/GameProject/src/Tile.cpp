#include "Tile.h"
#include <iostream>

Tile::Tile(int newX, int newY, double newWidth, double newHeight, Type newType)
{
    // Initialize positions
	xPos = newX;
	yPos = newY;

	// Initialize types and original types
	tileType = newType;
	originalType = newType;

	// initialize dimensions
	width = newWidth;
    height = newHeight;

    // initialize rotations
    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;

    // translations
    zoom = 0;

    // Initialize Quad
    vertices[0].x = -width / 2;
    vertices[0].y = -height / 2;
    vertices[0].z = zoom;

    vertices[1].x = width / 2;
    vertices[1].y = -height / 2;
    vertices[1].z = zoom;

    vertices[2].x = width / 2;
    vertices[2].y = height / 2;
    vertices[2].z = zoom;

    vertices[3].x = -width / 2;
    vertices[3].y = height / 2;
    vertices[3].z = zoom;

    texture = new TextureLoader();

    // Figure out which image to load for the texture. This is based on the type of the tile.
	string filepath;

	if(newType == Type::traversable)
        filepath = "Images/Tiles/StoneTile.png";
    else if(newType == Type::wall)
        filepath = "Images/Tiles/Wall.png";
    else if(newType == Type::arrows)
        filepath = "Images/Tiles/ArrowTile.png";
    else if(newType == Type::treasure)
        filepath = "Images/Tiles/TreasureTile.png";
    else
        // default tile for players and enemies. Players and enemies will be layered on top of these tiles
        filepath = "Images/Tiles/StoneTile.png";

    // Wrap the texture
    InitModel(filepath, true);
}


Tile::~Tile()
{

}

int Tile::GetType()
{
	return tileType;
}

void Tile::SetType(Type newType)
{
	tileType = newType;
}

bool Tile::IsTraversable()
{
    /*
    user can traverse any tile that isn't a wall. They can even run into enemies if they want.
    Therefore, we only need to know if the type is NOT a wall to know if the tile is traversable.
    Enemies will have extra logic in their Enemy::Move() function to prevent them from moving onto other enemies.
    */

	return tileType != wall;
}

bool Tile::IsTreasure()
{
	return tileType == treasure;
}

bool Tile::IsArrows()
{
	return tileType == arrows;
}

bool Tile::IsWall()
{
	return tileType == wall;
}

bool Tile::IsEnemy()
{
	return tileType == enemy;
}

bool Tile::IsPlayer()
{
    return tileType == player;
}

void Tile::RevertType()
{
    if(originalType == enemy || originalType == player)
        // players and enemies are layered on top of traversable tiles. If either moves off the tile, we want to set traversable, not back to enemy or player
        tileType = traversable;
    else
        tileType = originalType;
}

void Tile::RemoveArrows()
{
    // convert original type back to traversable once arrows have been picked up.
    originalType = Type::traversable;
    InitModel("Images/Tiles/StoneTile.png", true); // update image to plain stone tile
}
