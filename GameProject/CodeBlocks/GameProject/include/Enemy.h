#ifndef ENEMY_H
#define ENEMY_H

#include <Pathfinder.h>
#include <Grid.h>
#include <Player.h>


using namespace std;

class Pathfinder;

class Enemy : public Model
{
    public:
        Enemy();
        Enemy(double newX, double newY);
        virtual ~Enemy();

        void Move();
        void Update();

        void Destroy();

    protected:

    private:
        TextureLoader moveRight[4];
        TextureLoader moveLeft[4];
        TextureLoader moveDown[4];
        TextureLoader moveUp[4];
        TextureLoader idle[0];

        int moveFrame;

        int xDir, yDir, destX, destY;

        Timer* frameTimer;

        Pathfinder* pathfind;

        void InitAnimations();
        void Animate(string animation);

        float moveSpeed;
        void MoveToDestination();

        bool isMoving;
};

#endif // ENEMY_H
