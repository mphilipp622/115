#include "WinLose.h"

WinLose* WinLose::winLose;

WinLose::WinLose()
{
    //ctor
    winLose = this;
    gameOver = false;
    hasWon = false;
    hasLost = false;
}

WinLose::~WinLose()
{
    //dtor
}

void WinLose::Win()
{
    gameOver = true;
    hasWon = true;
    return;
}

void WinLose::Lose()
{
    gameOver = true;
    hasLost = true;
    return;
}

bool WinLose::IsGameOver()
{
    return gameOver;
}

bool WinLose::HasWon()
{
    return hasWon;
}

bool WinLose::HasLost()
{
    return hasLost;
}

void WinLose::Reset()
{
    hasLost = false;
    hasWon = false;
    gameOver = false;
}
