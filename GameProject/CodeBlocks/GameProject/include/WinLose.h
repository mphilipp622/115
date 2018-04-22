#ifndef WINLOSE_H
#define WINLOSE_H

//#include <SceneManager.h>
#include <iostream>
#include <UserInterface.h>

using namespace std;

class WinLose
{
    public:
        WinLose();
        virtual ~WinLose();

        void Win();
        void Lose();

        // HasWon and HasLost will be called on by GLScene for rendering UI elements to screen
        bool HasWon();
        bool HasLost();

        bool IsGameOver();

        static WinLose* winLose;

        // Sets data back to normal
        void Reset();

    protected:

    private:
        bool hasWon, hasLost;
        bool gameOver;
};

#endif // WINLOSE_H
