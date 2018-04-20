#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <Tile.h>
#include <Grid.h>
#include <cmath>
#include <queue>
#include <Player.h>
#include <map>
#include <tuple>

class Pathfinder
{
    public:
        Pathfinder();
        virtual ~Pathfinder();

        Tile* GetNextTile(int x, int y);

    protected:

    private:
        int ManhattanDistance(Tile* tile);
        int ManhattanDistance(int x, int y, int x1, int y1); // overloaded function used for tile-to-tile distances
        vector<Tile*> GetSuccessors(Tile* originTile);

        struct Node
        {
            Tile* tile;
            int fCost;
            int hCost;
            int gCost;

            vector<Tile*> path; // keeps track of the tiles we've visited to get here

            Node(Tile* newTile, int newG, int newH)
            {
                tile = newTile;
                hCost = newH;
                gCost = newG;
                fCost = gCost + hCost;
            }

            bool operator>(const struct Node& other) const
            {
                return fCost > other.fCost;
            }
        };

        struct MapKey
        {
            int x;
            int y;

            MapKey(int newX, int newY)
            {
                x = newX;
                y = newY;
            }

            bool operator < (const struct MapKey &other) const
            {
                return (x < other.x || y < other.y);
            }

            bool operator == (const struct MapKey &other) const
            {
                return (x == other.x && y == other.y);
            }


        };

        bool IsGoal(Node node);

};

#endif // PATHFINDER_H
