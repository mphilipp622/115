#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <Model.h>
#include <TextureLoader.h>
#include <Grid.h>
#include <Projectile.h>
#include <UserInterface.h>
#include <WinLose.h>

class Player : public Model
{
    public:
        Player();
        Player(double newX, double newY);
        virtual ~Player();

        void Move(double dirX, double dirY);
        void ShootProjectile(double x, double y);
        static Player* player;

        void Update();

        void SetLocked();

        void SetInput(WPARAM newParam);

        int GetArrowCount();

        void Die();

    protected:

    private:
        WPARAM wParam;
        int runFrame, idleFrame;
        TextureLoader run[4];
        TextureLoader idle[1];

        int arrowCount;

        bool playerLocked; // will be used to stop user input while arrows move
        bool isMoving;

        int destX, destY, xDir, yDir;

        void MoveToDestination();
};

#endif // PLAYER_H
