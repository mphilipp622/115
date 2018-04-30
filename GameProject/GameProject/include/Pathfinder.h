#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <Tile.h>
#include <Grid.h>
#include <cmath>
#include <queue>
#include <Player.h>
#include <map>
#include <tuple>

// Class that is used in the Enemy class to use A* pathfinding for finding their way to the player
class Pathfinder
{
    public:
        Pathfinder();
        virtual ~Pathfinder();

        // Returns the next tile in the shortest path. Called on by Enemy.
        Tile* GetNextTile(int startingX, int startingY);

    protected:

    private:
        // Returns the manhattan distance from the tile parameter TO the player tile
        int ManhattanDistance(Tile* tile);

        // overloaded function used for tile-to-tile distances
        int ManhattanDistance(int x, int y, int x1, int y1);

        // Returns the tiles above, below, left, and right of the originTile
        vector<Tile*> GetSuccessors(Tile* originTile);

        // struct that is used for A* pathfinding
        struct Node
        {
            Tile* tile; // the tile associated with this node
            int fCost; // fCost is always equal to hCost + gCost
            int hCost; // Minimum distance, regardless of obstacles, to get from here to player
            int gCost; // Running cost of movement to get to this tile.

            vector<Tile*> path; // keeps track of the tiles we've visited to get here

            Node(Tile* newTile, int newG, int newH)
            {
                // constructor for Node.
                tile = newTile;
                hCost = newH;
                gCost = newG;
                fCost = gCost + hCost;
            }

            // Overloaded greater than operator. Needed for Priority Queue implementation
            bool operator>(const struct Node& other) const
            {
                return fCost > other.fCost;
            }

            // Overloaded equality operator. Used for std::find.
            bool operator==(const struct Node& other) const
            {
                return (tile->GetX() == other.tile->GetX() && tile->GetY() == other.tile->GetY());
            }
        };

        // returns if the passed-in node contains the player tile
        bool IsGoal(Node node);
};

#endif // PATHFINDER_H
