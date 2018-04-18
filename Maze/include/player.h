/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>


using namespace std;

class Player
{
    public:
        Player();
        virtual ~Player();

        void drawplayer();             // Draw Player image
        void drawArrow();              // Draw Arrow
        void shootArrow();

        void initPlayer(int, char *);  // initialize the player with grid size
        void placePlayer(int,int);     // place the player
        void movePlayer(char *,int);   // move Player left,right,up,down
        void loadArrowImage(char *);   // set an image for the Arrow

        GridLoc getPlayerLoc();           // player current location
        GridLoc getArrowLoc();            // arrow current location


        loc converter(int, int);
        int frames;
        char *playerDir;

        void SetPosition(int, int);

        bool playerStatus;
        bool arrowStatus;
        bool livePlayer;
    protected:

        float t;
        void timer();                   // Timer for animation
        int gridSize;
        float unitWidth;                // Unit width of the grid
        int stepsPerMove;

    private:

    private:
        float xmax, xmin,ymax,ymin;
        GLuint plyTex;
        GLuint arrowTex;
        int arrXdir;
        int arrYdir;
        float arrAngle;
        loc arrowLoc;
        loc plyLoc;
};

#endif // PLAYER_H
