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

void Inputs::KeyPressed(Player* model, Grid* grid)
{
    // Handle key presses for model passed to this function
    const int aKey = 0x41, dKey = 0x44, sKey = 0x53, wKey = 0x57;
    // Use the unordered map of booleans to keep track of which keys are pressed. This allows multiple keys being pressed at once
    if(wParamKeys == aKey && grid->GetPlayer()->GetX() - 1.0 > 0) // includes boundary checking
    {
        int newX = grid->GetPlayer()->GetX() - 1.0;

        if(grid->GetTile(newX, grid->GetPlayer()->GetY())->IsTraversable())
            model->Move(-1.0, 0);
    }

    if(wParamKeys == dKey && grid->GetPlayer()->GetX() + 1.0 < grid->GetSizeX())
    {
        int newX = grid->GetPlayer()->GetX() - 1.0;

        if(grid->GetTile(newX, grid->GetPlayer()->GetY())->IsTraversable())
            model->Move(1.0, 0);
    }
    if(wParamKeys == sKey && grid->GetPlayer()->GetY() - 1.0 > 0)
    {
        int newY = grid->GetPlayer()->GetY() - 1.0;

        if(grid->GetTile(grid->GetPlayer()->GetX(), newY)->IsTraversable())
            model->Move(0, -1.0);
    }
    if(wParamKeys == wKey && grid->GetPlayer()->GetY() + 1.0 < grid->GetSizeY())
    {
        int newY = grid->GetPlayer()->GetY() + 1.0;

        if(grid->GetTile(grid->GetPlayer()->GetX(), newY)->IsTraversable())
            model->Move(0, 1.0);
    }

}

void Inputs::KeyUp(Player* model)
{
//    const int aKey = 0x41, dKey = 0x44, cKey = 0x43, bKey = 0x42;
//
//    if(keys["MoveLeft"] && wParamKeys == aKey)
//    {
//        model->SlowDown();
//        keys["MoveLeft"] = false;
//    }
//    if (keys["MoveRight"] && wParamKeys == dKey)
//    {
//        model->SlowDown();
//        keys["MoveRight"] = false;
//    }
//    if(keys["Jump"] && wParamKeys == VK_SPACE)
//    {
//        keys["Jump"] = false;
//    }
//    if(keys["PlayChord"] && wParamKeys == VK_SHIFT)
//    {
//        model->PlayChords(false);
//        keys["PlayChord"] = false;
//    }
}

void Inputs::MouseDown(Player* model, LPARAM lParam)
{
    // using 0x5 for lmouse and 0x6 for rmouse. For some reason, windows is sending those values when shift is held down instead of 0x1 and 0x2
    if(wParamMouse == 0x5)
    {
//        model->CheckUserInput(0, lParam);
//      convert mouse X and Y to openGL coordinates
        double screenHeight = GetSystemMetrics(SM_CYSCREEN); // get x size of screen
        double screenWidth = GetSystemMetrics(SM_CXSCREEN); //
        double aspectRatio = screenWidth / screenHeight;
        mousePosX = (LOWORD(lParam) / (screenWidth / 2) - 1.0) * aspectRatio * 3.33;
        mousePosY = -(HIWORD(lParam) / (screenHeight / 2) - 1.0) * 3.33;
        model->ShootProjectile(mousePosX, mousePosY);
//        model->ShootProjectile(mousePosX, mousePosY);
//        model->rotateX += currentY;
//        model->rotateY += currentX;
    }
//    if(wParamMouse == 0x6)
//        model->CheckUserInput(1, lParam);


//    prevMouseX = xNew;
//    prevMouseY = yNew;
}

void Inputs::MouseUp()
{

}
//
//void Inputs::WheelMove(Player* model, double delta)
//{
//     model->zoom += (delta / 120); // 120 is the default WHEEL_DELTA value in windows.h. This will constrain zoom to +/- 1.0
//}


void Inputs::SetMousePointer(double x, double y)
{
    mousePosX = x;
    mousePosY = y;
}
