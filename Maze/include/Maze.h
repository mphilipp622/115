/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */
#ifndef MAZE_H
#define MAZE_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>


using namespace std;



class Maze
{
    public:
        Maze();
        Maze(int);
        virtual ~Maze();

      void loadBackgroundImage(char *);   // set an image for the background
      void loadSetOfArrowsImage(char *);  // set an image for the Arrow Bundle
      void loadChestImage(char *);        // set an image for the Arrow

      void drawBackground();              // Draw background image
      void drawGrid();                    // Draw Grid
      void drawArrows();                  // Draw set of Arrows
      void drawChest();                   // Draw Chest

      int getGridSize();                  // return grid size
      loc converter(int, int);

      void placeChest(int,int);
      GridLoc GetChestLoc();

      void placeStArrws(int,int);
      GridLoc GetStArrwsLoc();

      int frames;
      float spin;
      bool liveChest;
      bool liveSetOfArrws;


    protected:
      float t;
      int gridSize;
      float unitWidth;                    // Unit width of the grid
  //    GLuint TextureLoader(char *);       // texture loder
    private:

      GLuint bakTex;                       // Handler for background texture
      GLuint ArrBnchTex;                   // Handler for set of arrows texture
      GLuint chestTex;                     // Handler for Chest texture
      loc chestLoc;
      loc setOfArrsLoc;
      float xmax, xmin,ymax,ymin;

};

#endif // MAZE_H
