#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <Model.h>
#include <DeltaTime.h>
#include <GLScene.h>
#include <algorithm>
#include <Timer.h>
#include <Grid.h>

using namespace std;

class Projectile : public Model
{
    public:
        Projectile();
        Projectile(double newX, double newY, double newWidth, double newHeight, int newDamage, float newSpeed, string newName, double newTargetX, double newTargetY);
        virtual ~Projectile();

        void Update();

    protected:
        int damage;
        float speed;
        double targetX, targetY;
        void Move();
        bool CheckCollision();
        void CheckCollisionEnemy();

    private:
        double vectorDist, normalizedX, normalizedY;
        double prevX, prevY;
        Timer *lifetime;
        double endOfLifeTime; // lifetime of 5 seconxs max

        // will remove projectile from gl scene vector and delete it
        void Destroy();
};

#endif // PROJECTILE_H