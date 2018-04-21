#include "WinLose.h"

WinLose* WinLose::winLose;

WinLose::WinLose()
{
    //ctor
    winLose = this;
}

WinLose::~WinLose()
{
    //dtor
}

void WinLose::Win()
{
    cout << "WIN" << endl;
    return;
}

void WinLose::Lose()
{
    cout << "LOSE" << endl;
    return;
}
