#ifndef WINLOSE_H
#define WINLOSE_H

//#include <SceneManager.h>
#include <iostream>

using namespace std;

class WinLose
{
    public:
        WinLose();
        virtual ~WinLose();

        void Win();
        void Lose();

        static WinLose* winLose;

    protected:

    private:
};

#endif // WINLOSE_H
