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

    protected:

    private:
        Pathfinder* pathfind;


};

#endif // ENEMY_H
