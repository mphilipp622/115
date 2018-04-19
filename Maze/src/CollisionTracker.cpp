#include "CollisionTracker.h"

CollisionTracker::CollisionTracker()
{
    //ctor
}

CollisionTracker::CollisionTracker(vector<vector<int>>newMap)
{
    // copy newMap into gridMap
    /*
        map key is as follows;
        0 = traversable tile
        1 = wall
        2 = enemy
        3 = player
        4 = chest
        5 = arrows
    */

    gridMap = newMap;
}


CollisionTracker::~CollisionTracker()
{
    //dtor
}

bool CollisionTracker::IsPlayer(int x, int y)
{
    return gridMap[x][y] == Type::player;
}

bool CollisionTracker::IsEnemy(int x, int y)
{
    return gridMap[x][y] == Type::enemy;
}

bool CollisionTracker::IsArrows(int x, int y)
{
    return gridMap[x][y] == Type::arrow;
}

bool CollisionTracker::IsTreasure(int x, int y)
{
    return gridMap[x][y] == Type::treasure;
}

bool CollisionTracker::IsTraversable(int x, int y)
{
    return gridMap[x][y] == Type::traversable;
}

void CollisionTracker::UpdatePlayerPosition(int x, int y)
{
    if(gridMap[x][y] != Type::wall)
    {
        gridMap[playerX][playerY] = Type::traversable;
        gridMap[x][y] = Type::player;
    }
}

void CollisionTracker::UpdateEnemyPosition(int x, int y, int oldX, int oldY)
{

}
