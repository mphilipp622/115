#ifndef PLAYER_H
#define PLAYER_H

#include <Model.h>
#include <TextureLoader.h>

class Player : public Model
{
    public:
        Player();
        Player(double newX, double newY);
        virtual ~Player();

        void InitPlayer();

        void Move(double dirX, double dirY);

        static Player* player;

    protected:

    private:
        int runFrame, idleFrame;
        TextureLoader run[4];
        TextureLoader idle[1];
};

#endif // PLAYER_H
