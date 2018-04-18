/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef WALL_H
#define WALL_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>



class wall
{
    public:
        wall();
        virtual ~wall();
        wall(int);

            void drawWall();               // Draw the Maze wall
            void wallInit(int, char *);
            void placeWall(int, int);

            float unitWidth;
            int gridSize;
            loc converter(int , int );
            loc wallBrk;
            bool liveWall;
    protected:

    private:
              GLuint wallTex;
};

#endif // WALL_H
