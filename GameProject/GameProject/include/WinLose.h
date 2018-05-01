#ifndef WINLOSE_H
#define WINLOSE_H

//#include <SceneManager.h>
#include <iostream>
#include <UserInterface.h>

using namespace std;

// Class for keeping track of win and lose conditions. This class is mostly useful because Player and Enemy can
// set win and lose states depending on their actions, which can then be accessed by GLScene to execute functionality.
class WinLose
{
    public:
        WinLose();
        virtual ~WinLose();

        // Sets global win/lose state to Win
        void Win();

        // Sets global Win/Lose state to Lose
        void Lose();

        // HasWon and HasLost will be called on by GLScene for rendering UI elements to screen
        bool HasWon();
        bool HasLost();

        // Returns if the game is over. Game is over if either win or lose condition has been met
        bool IsGameOver();

        // Global Accessor for WinLose. Accessed by Player, Enemy, and GLScene
        static WinLose* winLose;

    protected:

    private:
        // state trackers
        bool hasWon, hasLost;
        bool gameOver;
};

#endif // WINLOSE_H
