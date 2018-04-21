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

        // Called on by Player to remove an arrow from the HUD
        void RemoveArrow();

        static UserInterface* UI;

    protected:

    private:
        double scaleX, scaleY;
        vector<Model*> arrows;
};

#endif // USERINTERFACE_H
