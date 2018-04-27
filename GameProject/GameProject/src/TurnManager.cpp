#include "TurnManager.h"

TurnManager* TurnManager::turnManager;

TurnManager::TurnManager()
{
    //ctor

    turn = 0;

    turnManager = this; // create global instance
}

TurnManager::~TurnManager()
{
    //dtor
}

bool TurnManager::IsPlayerTurn()
{
    return turn == 0;
}

bool TurnManager::IsEnemyTurn()
{
    return turn == 1;
}

void TurnManager::NextTurn()
{
    turn = !turn;
}

void TurnManager::SetTurn(int newTurn)
{
    turn = newTurn;
}
