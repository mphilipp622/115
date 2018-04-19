#ifndef COLLISIONTRACKER_H
#define COLLISIONTRACKER_H

#include <vector>

using namespace std;

// This class will be used by player and enemy to determine the locations of different elements in the game.
class CollisionTracker
{
    public:
        CollisionTracker();
        CollisionTracker(vector<vector<int>> newMap);
        virtual ~CollisionTracker();

        bool IsPlayer(int x, int y);
        bool IsEnemy(int x, int y);
        bool IsArrows(int x, int y);
        bool IsTreasure(int x, int y);
        bool IsTraversable(int x, int y);

        void UpdatePlayerPosition(int x, int y);
        void UpdateEnemyPosition(int x, int y, int oldX, int oldY);

    protected:

    private:
        vector<vector<int>> gridMap;

        int playerX, playerY;

        enum Type{ traversable = 0, wall = 1, enemy = 2, player = 3, treasure = 4, arrow = 5};
};

#endif // COLLISIONTRACKER_H
