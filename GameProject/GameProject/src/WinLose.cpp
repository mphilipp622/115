#include "WinLose.h"

WinLose* WinLose::winLose;

WinLose::WinLose()
{
    if(winLose)
        delete winLose; // if winLose already exists, remove it

    winLose = this;

    // initialize states to false
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
    // Set states to gameOver and Win
    gameOver = true;
    hasWon = true;
}

void WinLose::Lose()
{
    // Set States to gameOver and Lose
    gameOver = true;
    hasLost = true;
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
