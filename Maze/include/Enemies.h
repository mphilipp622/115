/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef ENEMIES_H
#define ENEMIES_H

#include<CommonThings.h>
#include <Maze.h>
#include <time.h>
#include <thread>
#include <string>


class Enemies
{
    public:
        Enemies();
        virtual ~Enemies();
        void initEnm(int, int, char *);

        void placeEnemy(int,int);       // place enemy
        void drawEnemy();
        void moveEnemy(string);     // move Enemy left,right,up,down
        void animate();
        GridLoc getEnemyLoc();              // Enemy current location


        int gridSize;
        float unitWidth;                // Unit width of the grid
        int stepsPerMove;

    protected:

    private:
         int frames;                      //number of frames generally
         float t;
         GLuint enmTex;

         float xmax, xmin,ymax,ymin;
         bool up,down,left,right;
         float moveDis=0;
         loc enmLoc;
};

#endif // ENEMIES_H
