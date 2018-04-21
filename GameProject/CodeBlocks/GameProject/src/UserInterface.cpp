#include "UserInterface.h"

UserInterface* UserInterface::UI;

UserInterface::UserInterface()
{
    //ctor
    UI = this;
    // scales are used for placing arrow icons at the right place on screen in relation to the maze
    scaleX = -0.5;
    scaleY = 1.2;

    for(int i = 0; i < Player::player->GetArrowCount(); i++)
        AddArrow();

}

UserInterface::~UserInterface()
{
    //dtor
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
    arrows.push_back(new Model(0.2, 0.5, -0.5 + arrows.size() * 0.2, Grid::grid->GetSizeY() - 1.2 , "ArrowUI", "UI"));
    arrows.back()->InitModel("Images/ArrowUp.png", true);
    arrows.back()->SetZoom(4.0);
}

void UserInterface::RemoveArrow()
{
    delete arrows.back();
    arrows.pop_back();
}
