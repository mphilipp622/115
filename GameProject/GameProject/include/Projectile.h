#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <Model.h>
#include <DeltaTime.h>
#include <GLScene.h>
#include <algorithm>
#include <Timer.h>
#include <Grid.h>

using namespace std;

// Class for handling Arrow movement and destruction
class Projectile : public Model
{
    public:
        Projectile();
        Projectile(double newX, double newY, double newWidth, double newHeight, float newSpeed, string newName, double newdirX, double newDirY);
        virtual ~Projectile();

        // Called by GLScene::DrawGLScene. Moves the arrow in increments across the screen
        void Update();

    protected:


    private:
        float speed; // dictates the speed of the arrow
        double xDir, yDir; // x and y coordinates of the target. Basically x and y directions

        // Moves the arrow in the scene
        void Move();

        // Checks collision against static objects, such as walls
        bool CheckCollision();

        // Checks collision against enemies and destroys them.
        void CheckCollisionEnemy();

        // used for calculating arrow path. Not necessary for manhattan paths, but useful for diagonal paths.
        double vectorDist, normalizedX, normalizedY;

        // used for destroying arrows if they've managed to hit nothing for a long time. Necessary for freeing memory.
        Timer *lifetime;
        double endOfLifeTime; // lifetime of 5 seconds

        // will remove projectile from gl scene vector and delete it
        void Destroy();
};

#endif // PROJECTILE_H
