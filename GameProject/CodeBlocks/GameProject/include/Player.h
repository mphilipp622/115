#ifndef PLAYER_H
#define PLAYER_H

#include <Model.h>
#include <TextureLoader.h>
#include <Grid.h>
#include <TurnManager.h>

class Player : public Model
{
    public:
        Player();
        Player(double newX, double newY);
        virtual ~Player();

        void Move(double dirX, double dirY);
        void ShootProjectile(double x, double y);
        static Player* player;

    protected:

    private:
        int runFrame, idleFrame;
        TextureLoader run[4];
        TextureLoader idle[1];
};

#endif // PLAYER_H
