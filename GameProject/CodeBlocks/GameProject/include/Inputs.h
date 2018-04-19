#ifndef INPUTS_H
#define INPUTS_H

#include <windows.h>
#include <iostream>
#include <Model.h>
#include <unordered_map>
#include <string>
#include <Player.h>
#include <Grid.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void KeyPressed(Player*, Grid*);
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
