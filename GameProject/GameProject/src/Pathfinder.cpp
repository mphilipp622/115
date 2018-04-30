#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
    //ctor
}

Pathfinder::~Pathfinder()
{
    //dtor
}

Tile* Pathfinder::GetNextTile(int startingX, int startingY)
{
    // A* pathfinding implementation.

    priority_queue<Node, vector<Node>, greater<Node> > frontier; // ascending order priority queue for Nodes

    vector<Node> visitedNodes; // list of visited nodes

    // First node will hav eg cost 0.
    Node startNode = Node(Grid::grid->GetTile(startingX, startingY), 0,
                          ManhattanDistance(Grid::grid->GetTile(startingX, startingY)));

    frontier.push(startNode); // push start node onto frontier

    while(!frontier.empty())
    {
        Node currentNode = frontier.top(); // grab next node
        frontier.pop(); // remove it from priority queue

        if(find(visitedNodes.begin(), visitedNodes.end(), currentNode) != visitedNodes.end())
            // node is already visited, continue
            continue;

        if(IsGoal(currentNode))
        {
            // this node contains our player, grab the 0th index of the node's path
            if(currentNode.path.size() > 0 && !currentNode.path.at(0)->IsEnemy())
                return currentNode.path.at(0);

            return startNode.tile; // basically, if we found no path or our next tile is an enemy, we don't move
        }

        visitedNodes.push_back( currentNode); // add current node to our list of visited nodes

        // Get Adjacency matrix for current tile and iterate over it
        for(auto& tile : GetSuccessors(currentNode.tile))
        {
            // since all movement costs are 1, we can use the path size + 1 to get current gCost
            Node nextNode = Node(tile, currentNode.path.size() + 1, ManhattanDistance(tile));

            for(int i = 0; i < currentNode.path.size(); i++)
                nextNode.path.push_back(currentNode.path[i]); // add previous path to this path

            nextNode.path.push_back(tile); // add this node to the path

            if(find(visitedNodes.begin(), visitedNodes.end(), nextNode) == visitedNodes.end())
                // Add this node to the priority queue if it hasn't already been added to the visitedNodes
                frontier.push(nextNode);

        }
    }

    // This only happens if we don't find a path. This will result in the enemy staying in position.
    return startNode.tile;
}

int Pathfinder::ManhattanDistance(Tile* tile)
{
    // calculates manhattan distance between this node and the player. Used for our Heuristic value
    return abs(tile->GetX() - Player::player->GetX()) + abs(tile->GetY() - Player::player->GetY());
}

int Pathfinder::ManhattanDistance(int x, int y, int x1, int y1)
{
    // Heuristic calculation between two different (x, y) pairs
    return abs(x - x1) + abs(y - y1);
}

vector<Tile*> Pathfinder::GetSuccessors(Tile* originTile)
{
    // initialize list
    vector<Tile*> successors;

    // start from bottom left tile from origin and move right and up and get successors.
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue; // skip the origin tile's position

            if(!Grid::grid->BoundSafe(originTile->GetX() + j, originTile->GetY() + i))
                // Ensure adjacent tile is within grid boundaries and is NOT a wall
                continue;

            if(ManhattanDistance(originTile->GetX(), originTile->GetY(), originTile->GetX() + j, originTile->GetY() + i) > 1)
                continue; // rule out any diagonal tiles

            // push this tile onto the successor list
            successors.push_back(Grid::grid->GetTile(originTile->GetX() + j, originTile->GetY() + i));
        }
    }

    return successors;
}

bool Pathfinder::IsGoal(Node node)
{
    // returns if this node contains the tile the player is on.

    if(node.tile->GetX() == Player::player->GetX() && node.tile->GetY() == Player::player->GetY())
        return true;

    return false;
}
