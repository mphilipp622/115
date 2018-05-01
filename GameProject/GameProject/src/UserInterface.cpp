#include "UserInterface.h"
#include <cmath>

UserInterface* UserInterface::UI;

UserInterface::UserInterface()
{
    //ctor

    if(UI)
        delete UI; // if a static UI already exists, delete it

    UI = this; // set the static instance of UI

    // scales are used for placing arrow icons at the right place on screen in relation to the maze
    scaleX = -0.5;
    scaleY = 0.5;

    // UI will be rendered at z value of 1
    UIZoom = 1;

    // Center of the screen will be the center of the grid due to gluLookAt() function in GLScene::DrawGLScene()
    centerX = (double) Grid::grid->GetSizeX() / 2;
    centerY = (double) Grid::grid->GetSizeY() / 2;

    // For every arrow the player has, we add a new arrow icon. Player currently starts with 1 arrow, but we could start with more and this code would work.
    for(int i = 0; i < Player::player->GetArrowCount(); i++)
        AddArrow();

    // Initialize UI elements and wrap their textures
    InitElements();
}

UserInterface::~UserInterface()
{
    //dtor
}

void UserInterface::InitElements()
{
    // Initialize Models
    youWin = new Model(3.5, 3.5, centerX, centerY, "YouWinPanel", "UI");
    youLose = new Model(3.5, 3.5, centerX, centerY, "YouLosePanel", "UI");
    playAgainButton = new Model(2.0, 0.5, centerX, centerY - 0.3, "PlayAgainButton", "UI");
    mainMenuButton = new Model(2.0, 0.5, centerX, centerY - 0.3 - 0.7, "MainMenuButton", "UI");

    // Bind textures to all the models
    youWin->InitModel("Images/UI/YouWin.png", true);
    youLose->InitModel("Images/UI/YouLose.png", true);
    playAgainButton->InitModel("Images/UI/PlayAgain.png", true);
    mainMenuButton->InitModel("Images/UI/MainMenu.png", true);

    // Set z positions for the models
    youWin->SetZoom(UIZoom);
    youLose->SetZoom(UIZoom);
    playAgainButton->SetZoom(UIZoom);
    mainMenuButton->SetZoom(UIZoom);
}

void UserInterface::DrawArrows()
{
    // Draw all the arrows to the top of the screen
    for(auto& arrow : arrows)
        arrow->DrawModel();
}

void UserInterface::AddArrow()
{
    // Add arrow icon to the UI when the player picks up a new arrow

    // -3.33 + arrows.size() will hopefully generate new models to the right of the previous model
    // -0.5 + arrows.size() * 0.1 should keep the arrow icons in a decent spot. 0.1 is icon width / 2
    // Honestly, these numbers are the result of guess and check
    arrows.push_back(new Model(0.2, 0.5, scaleX + arrows.size() * 0.2, Grid::grid->GetSizeY() - scaleY , "ArrowUI", "UI"));

    // Grab the new arrow and initialize the texture and set the z position. Will be rendered in DrawArrows()
    arrows.back()->InitModel("Images/UI/ArrowUp.png", true);
    arrows.back()->SetZoom(UIZoom);
}

void UserInterface::RemoveArrow()
{
    delete arrows.back(); // delete the arrow pointer from the back of the vector
    arrows.pop_back(); // shrink the vector by 1
}

void UserInterface::YouWin()
{
    // Draw the Win panel with associated buttons
    youWin->DrawModel();
    playAgainButton->DrawModel();
    mainMenuButton->DrawModel();
}

void UserInterface::YouLose()
{
    // Draw the lose panel with associated buttons
    youLose->DrawModel();
    playAgainButton->DrawModel();
    mainMenuButton->DrawModel();
}
