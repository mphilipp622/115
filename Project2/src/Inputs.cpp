#include <Inputs.h>
#include <iostream>
#include <DeltaTime.h>
#include <string>

using namespace std;


Inputs::Inputs()
{
}

Inputs::~Inputs()
{
}

//Global variable for acceleration, might want to
//implement into the model class later on.
void Inputs::KeyPressed(Player* model)
{
    // Handle key presses for model passed to this function
    const int aKey = 0x41, dKey = 0x44, wKey = 0x57, sKey = 0x53;

    // Use the unordered map of booleans to keep track of which keys are pressed. This allows multiple keys being pressed at once
    if(wParam == aKey || wParam == VK_UP)
        model->MoveX(-1);
    if(wParam == dKey || wParam == VK_RIGHT)
        model->MoveX(1);
    if(wParam == sKey || wParam == VK_LEFT)
        model->MoveY(-1);
    if(wParam == wKey || wParam == VK_DOWN)
        model->MoveY(1);
}

void Inputs::KeyUp(Player* model)
{
//    const int aKey = 0x41, dKey = 0x44, wKey = 0x57, sKey = 0x53;
//
//    if(keys["MoveLeft"] && wParam == aKey)
//    {
//        model->SlowDown();
//        keys["MoveLeft"] = false;
//    }
//    if (keys["MoveRight"] && wParam == dKey)
//    {
//        model->SlowDown();
//        keys["MoveRight"] = false;
//    }
//    if(keys["Jump"] && wParam == VK_SPACE)
//    {
//        keys["Jump"] = false;
//    }
}
