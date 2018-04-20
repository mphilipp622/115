#include "Enemy.h"

Enemy::Enemy()
{
    //ctor
}

Enemy::Enemy(double newX, double newY)
{
    xPos = newX;
	yPos = newY;

	width = 1.0;
    height = 1.0;

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
    pathfind = new Pathfinder();

    InitModel("Images/Enemy/EnemyLeft.png", true);
}

Enemy::~Enemy()
{
    //dtor
}



void Enemy::Move()
{
    Tile* tempTile = pathfind->GetNextTile(xPos, yPos);

    // once we've found our next tile, move enemy into it and set types accordingly.
    Grid::grid->GetTile(xPos, yPos)->SetType(Type::traversable);
    SetPosition(tempTile->GetX(), tempTile->GetY());
    Grid::grid->GetTile(xPos, yPos)->SetType(Type::enemy); // tile now has enemy
}

