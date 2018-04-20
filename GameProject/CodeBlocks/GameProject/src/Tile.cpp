#include "Tile.h"
#include <iostream>

Tile::Tile(int newX, int newY, double newWidth, double newHeight, Type newType)
{
	xPos = newX;
	yPos = newY;
	tileType = newType;

	width = newWidth;
    height = newHeight;

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
        filepath = "Images/Tiles/StoneTile.png"; // default tile for players and enemies. Players and enemies will be layered on top of these tiles
//    else if(newType == Type::player)
//        filepath = "Images/Player/play.png";
//    else if(newType == Type::enemy)
//        filepath = "Images/Enemy/EnemyLeft.png";

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
	return tileType != Type::wall; // user can traverse any tile that isn't a wall. They can even run into enemies if they want.
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

