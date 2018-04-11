#include "stdafx.h"
#include "Tile.h"


Tile::Tile(int newX, int newY, Type newType)
{
	xPos = newX;
	yPos = newY;
	tileType = newType;
}


Tile::~Tile()
{
}

int Tile::GetX()
{
	return xPos;
}

int Tile::GetY()
{
	return yPos;
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
	return tileType == Type::traversable;
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
