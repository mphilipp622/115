#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Player.h>
#include <Model.h>
#include <Grid.h>
#include <vector>

using namespace std;

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

        void YouWin();

        void YouLose();

        // Checks user input to see if user has clicked any buttons. Executes scene loads accordingly.
        void CheckInput(int selection);

        static UserInterface* UI;

        // sets ui back to normal
        void Reset();

    protected:

    private:
        double scaleX, scaleY;
        double UIZoom;
        double centerX, centerY;

        vector<Model*> arrows;

        // Will load scenes based on which buttons are clicked by user
        void LoadScene();

        // different models for rendering win and loss messages to screen
        Model* youWin;
        Model* youLose;
        Model* playAgainButton;
        Model* mainMenuButton;

        void InitElements();
};

#endif // USERINTERFACE_H
