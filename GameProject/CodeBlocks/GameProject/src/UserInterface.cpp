#include "UserInterface.h"
#include <cmath>

UserInterface* UserInterface::UI;

UserInterface::UserInterface()
{
    //ctor

    if(UI)
        delete UI;

    UI = this;
    // scales are used for placing arrow icons at the right place on screen in relation to the maze
    scaleX = -0.5;
    scaleY = 0.5;

    UIZoom = 1;

    centerX = (double) Grid::grid->GetSizeX() / 2;
    centerY = (double) Grid::grid->GetSizeY() / 2;

    for(int i = 0; i < Player::player->GetArrowCount(); i++)
        AddArrow();

    youWin = new Model(3.5, 3.5, centerX, centerY, "YouWinPanel", "UI");
    youLose = new Model(3.5, 3.5, centerX, centerY, "YouLosePanel", "UI");
    playAgainButton = new Model(2.0, 0.5, centerX, centerY - 0.3, "PlayAgainButton", "UI");
    mainMenuButton = new Model(2.0, 0.5, centerX, centerY - 0.3 - 0.7, "MainMenuButton", "UI");

    InitElements();
}

UserInterface::~UserInterface()
{
    //dtor
}

void UserInterface::InitElements()
{
    // Bind textures to all the models
    youWin->InitModel("Images/UI/YouWin.png", true);
    youLose->InitModel("Images/UI/YouLose.png", true);
    playAgainButton->InitModel("Images/UI/PlayAgain.png", true);
    mainMenuButton->InitModel("Images/UI/MainMenu.png", true);

    youWin->SetZoom(UIZoom);
    youLose->SetZoom(UIZoom);
    playAgainButton->SetZoom(UIZoom);
    mainMenuButton->SetZoom(UIZoom);
}

void UserInterface::DrawArrows()
{
    for(auto& arrow : arrows)
        arrow->DrawModel();

}

void UserInterface::AddArrow()
{
    // -3.33 + arrows.size() will hopefully generate new models to the right of the previous model
    // -0.5 + arrows.size() * 0.1 should keep the arrow icons in a decent spot. 0.2 is icon width
    arrows.push_back(new Model(0.2, 0.5, scaleX + arrows.size() * 0.2, Grid::grid->GetSizeY() - scaleY , "ArrowUI", "UI"));
    arrows.back()->InitModel("Images/UI/ArrowUp.png", true);
    arrows.back()->SetZoom(UIZoom);
}

void UserInterface::RemoveArrow()
{
    delete arrows.back();
    arrows.pop_back();
}

void UserInterface::YouWin()
{
    youWin->DrawModel();
    playAgainButton->DrawModel();
    mainMenuButton->DrawModel();
}

void UserInterface::YouLose()
{
    youLose->DrawModel();
    playAgainButton->DrawModel();
    mainMenuButton->DrawModel();
}


void UserInterface::LoadScene()
{

}

void UserInterface::CheckInput(int selection)
{
    if(selection == 1)
         cout << "Play Again" << endl;
    else if(selection == 2)
         cout << "Main Menu" << endl;
}

void UserInterface::Reset()
{
    for(int i = 0; i < arrows.size(); i++)
        delete arrows[i];
}
