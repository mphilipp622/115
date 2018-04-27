#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <string>
#include <Player.h>

class Player;

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void KeyPressed(Player*);
        void KeyUp(Player* model);
//
        void MouseDown(Player*, LPARAM lParam);
        void MouseUp();
//        void WheelMove(Player*, double);
        void SetMousePointer(double x, double y);

        double prevMouseX, prevMouseY;

        WPARAM wParamKeys, wParamMouse;

    protected:

    private:
        double mousePosX, mousePosY;
};

#endif // INPUTS_H
