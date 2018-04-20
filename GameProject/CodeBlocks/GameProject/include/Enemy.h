#ifndef ENEMY_H
#define ENEMY_H

#include <Player.h>
#include <Grid.h>
#include <Pathfinder.h>
#include <TurnManager.h>

using namespace std;

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
