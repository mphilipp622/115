#include "TurnManager.h"

TurnManager* TurnManager::turnManager;

TurnManager::TurnManager()
{
    //ctor

    turn = 0;

    if(turnManager)
        delete turnManager; // if the global instance already exists from a previous scene, delete it

    turnManager = this; // create global instance
}

TurnManager::~TurnManager()
{
    //dtor
}

bool TurnManager::IsPlayerTurn()
{
    return turn == 0; // player turn is 0
}

bool TurnManager::IsEnemyTurn()
{
    return turn == 1; // enemy turn is 1
}

void TurnManager::NextTurn()
{
    turn = !turn; // invert the current turn to set next turn
}
