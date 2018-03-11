#ifndef PLAYER_H
#define PLAYER_H

#include <GL\GL.h>
#include <Model.h>
#include <TextureLoader.h>
#include <DeltaTime.h>

typedef struct
{
    float x, y, z;
}vec1;

// class for player character. Inherits from Model for positions/rotations/etc.
class Player : public Model
{
    public:
        Player();
        Player(int newX, int newY);
        virtual ~Player();

        // Graphics
        float scaleSize[3] = {1.0, 1.0, 1.0}; // x, y, z scale values
        vec1 vertices[4]; // 4 vertices of xyz values
        void DrawPlayer();
        void InitPlayer();

        // Animation
        int actionTrigger;
        void Actions(int newAction);

        void Update();

        // Character Controller Functions

        void MoveX(int direction);
        void MoveY(int direction);
        void ShootArrow();
        void AddArrow();

        // global instance of player object
        static Player* player;

        // get z axis value
        double GetZoom();


    protected:

    private:
        int arrows;
        int prevXPos, prevYPos;
        double playerZoom;
};

#endif // PLAYER_H
