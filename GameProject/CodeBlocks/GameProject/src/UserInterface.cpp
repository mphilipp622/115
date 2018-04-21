#include "UserInterface.h"

UserInterface::UserInterface()
{
    //ctor
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
    {
        arrow->DrawModel();
        cout << "Drawing Arrow" << endl;
    }

}

void UserInterface::AddArrow()
{
    // -3.33 + arrows.size() will hopefully generate new models to the right of the previous model
    arrows.push_back(new Model(1.0, 1.0, 0, 0, "ArrowUI", "UI"));
    arrows.back()->InitModel("ArrowUp.png", true);
}

void UserInterface::RemoveArrow()
{
    delete arrows.back();
    arrows.pop_back();
}
