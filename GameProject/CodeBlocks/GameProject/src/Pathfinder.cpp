#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
    //ctor
}

Pathfinder::~Pathfinder()
{
    //dtor
}

Tile* Pathfinder::GetNextTile(int x, int y)
{
    // A* pathfinding implementation.

    priority_queue<Node, vector<Node>, greater<Node> > frontier; // ascending order priority queue for Nodes
    map<MapKey, Node> visitedNodes;

    Node startNode = Node(Grid::grid->GetTile(x, y), 0, ManhattanDistance(Grid::grid->GetTile(x, y)));
    frontier.push(startNode);

    while(!frontier.empty())
    {
        Node currentNode = frontier.top(); // grab next node
        frontier.pop(); // remove it from priority queue

        if(!visitedNodes.empty() && visitedNodes.find(MapKey(currentNode.tile->GetX(), currentNode.tile->GetY())) != visitedNodes.end())
            // node is already visited, continue
            continue;

        if(IsGoal(currentNode))
        {
            // this node contains our player, grab the 0th index of the node's path
            if(currentNode.path.size() > 0 && !currentNode.path.at(0)->IsEnemy())
                return currentNode.path.at(0);

            return currentNode.tile; // this case should never happen, but putting it in just in case
        }

        MapKey newKey = MapKey(currentNode.tile->GetX(), currentNode.tile->GetY());
        visitedNodes.insert( { newKey, currentNode } ); // add current node to our list of visited nodes

        for(auto& tile : GetSuccessors(currentNode.tile))
        {
            Node nextNode = Node(tile, currentNode.path.size() + 1, ManhattanDistance(tile));

            for(int i = 0; i < currentNode.path.size(); i++)
                nextNode.path.push_back(currentNode.path[i]); // add previous path to this path

            nextNode.path.push_back(tile); // add this node to the path

            if(visitedNodes.find(MapKey(tile->GetX(), tile->GetY())) == visitedNodes.end())
                // Add this node to the priority queue if it hasn't already been added to the visitedNodes
                frontier.push(nextNode);

        }
    }
}

int Pathfinder::ManhattanDistance(Tile* tile)
{
    // calculates manhattan distance between this node and the player. Used for our Heuristic value
    return abs(tile->GetX() - Player::player->GetX()) + abs(tile->GetY() - Player::player->GetY());
}

int Pathfinder::ManhattanDistance(int x, int y, int x1, int y1)
{
    return abs(x - x1) + abs(y - y1);
}

vector<Tile*> Pathfinder::GetSuccessors(Tile* originTile)
{
    vector<Tile*> successors;

    // start from top left tile from origin and move right and down and get successors.
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue; // skip the current tile

            if(!Grid::grid->BoundSafe(originTile->GetX() + j, originTile->GetY() + i))
                continue;

//            if(Grid::grid->GetTile(originTile->GetX() + j, originTile->GetY() + i)->IsEnemy())
//                continue; // ignore if enemy already occupies tile.

//            if(Grid::grid->GetTile(originTile->GetX() + j, originTile->GetY() + i)->IsWall())
//                continue;

            if(ManhattanDistance(originTile->GetX(), originTile->GetY(), originTile->GetX() + j, originTile->GetY() + i) > 1)
                continue;

            successors.push_back(Grid::grid->GetTile(originTile->GetX() + j, originTile->GetY() + i));
        }
    }

    return successors;
}

bool Pathfinder::IsGoal(Node node)
{
    if(node.tile->GetX() == Player::player->GetX() && node.tile->GetY() == Player::player->GetY())
        return true;

    return false;
}
