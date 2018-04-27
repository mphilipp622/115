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
//    map<MapKey, Node> visitedNodes;
    vector<Node> visitedNodes;
    Node startNode = Node(Grid::grid->GetTile(x, y), 0, ManhattanDistance(Grid::grid->GetTile(x, y)));
    frontier.push(startNode);

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

//        MapKey newKey = MapKey(currentNode.tile->GetX(), currentNode.tile->GetY());
        visitedNodes.push_back( currentNode); // add current node to our list of visited nodes

        for(auto& tile : GetSuccessors(currentNode.tile))
        {

            Node nextNode = Node(tile, currentNode.path.size() + 1, ManhattanDistance(tile));

            for(int i = 0; i < currentNode.path.size(); i++)
                nextNode.path.push_back(currentNode.path[i]); // add previous path to this path

            nextNode.path.push_back(tile); // add this node to the path

            if(find(visitedNodes.begin(), visitedNodes.end(), nextNode) == visitedNodes.end())
                // Add this node to the priority queue if it hasn't already been added to the visitedNodes
                frontier.push(nextNode);

        }
    }

    return startNode.tile;
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

//    cout << "Successors of (" << originTile->GetX() << ", " << originTile->GetY() << ") " << endl;
    // start from bottom left tile from origin and move right and up and get successors.
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue; // skip the current tile

            if(!Grid::grid->BoundSafe(originTile->GetX() + j, originTile->GetY() + i))
                continue;

            if(ManhattanDistance(originTile->GetX(), originTile->GetY(), originTile->GetX() + j, originTile->GetY() + i) > 1)
                continue; // rule out any diagonal tiles

            successors.push_back(Grid::grid->GetTile(originTile->GetX() + j, originTile->GetY() + i));
        }
    }

//    for(auto& i : successors)
//        cout << i->GetX() << ", " << i->GetY() << endl;
//    cout << endl;
    return successors;
}

bool Pathfinder::IsGoal(Node node)
{
    if(node.tile->GetX() == Player::player->GetX() && node.tile->GetY() == Player::player->GetY())
        return true;

    return false;
}

bool Pathfinder::ContainsEnemy(Node node)
{
    for(auto& tile : node.path)
    {
        if(tile->IsEnemy())
            return true;
    }

    return false;
}
