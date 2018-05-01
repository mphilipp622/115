#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Player.h>
#include <Model.h>
#include <Grid.h>
#include <vector>

using namespace std;

// This class displays UI elements such as arrows at the top of the screen. It also handles displaying Win/Lose messages
class UserInterface
{
    public:
        UserInterface();
        virtual ~UserInterface();

        // renders arrows to screen
        void DrawArrows();

        // When Player picks up an arrow, this should be called on to add a new arrow to HUD
        void AddArrow();

        // CalledSelectButton(0); on by Player to remove an arrow from the HUD
        void RemoveArrow();

        // Draws the Win message and associated graphics to the screen
        void YouWin();

        // Draws the Lose message and associated graphics to screen
        void YouLose();

        // Global, static accessor for the UI. Used by Player and GLScene
        static UserInterface* UI;

    protected:

    private:
        // scales are used for placing arrow icons at the right place on screen in relation to the maze
        double scaleX, scaleY;

        // Z position for UI elements
        double UIZoom;

        // Origin positions for the UI. Determines where (0, 0) is for the UI
        double centerX, centerY;

        // Container for the arrow icons
        vector<Model*> arrows;

        // different models for rendering win and loss messages to screen
        Model* youWin;
        Model* youLose;
        Model* playAgainButton;
        Model* mainMenuButton;

        // Initializes textures to the UI Elements
        void InitElements();
};

#endif // USERINTERFACE_H
