/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */

#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <Enemies.h>

#include <wall.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <CollisionTracker.h>

/* GLUT callback Handlers */

using namespace std;

Maze *M;
Player *P;

vector<vector<int>> gridMap;

wall W[100];
Enemies E[100];
Timer *T0 = new Timer();

CollisionTracker* collision;

string mapFilePath = "Maps/TestMap.txt";

int wallCount = 0;
int enemyCount = 0;

float wWidth, wHeight;
float xPos,yPos;
bool move =true;

float a;

void display(void);

void resize(int width, int height)
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void init()
{

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ifstream in(mapFilePath);

    string line;
    int gridSizeX = 0;
    int gridSizeY = 0;

	for (int i = 0; !in.eof(); i++)
	{
		getline(in, line); // read first row of data
		gridMap.push_back(vector<int>());
		gridSizeX = line.size();

		for (int j = 0; j < gridSizeX; j++)
			gridMap[i].push_back(line.at(j) - '0'); // convert from ascii to int

		gridSizeY = i + 1;
	}

    M = new Maze(gridSizeX);
    P = new Player();
    collision = new CollisionTracker(gridMap);

    for(int i = 0; i < gridSizeY; i++)
    {
        for(int j = 0; j < gridSizeX; j++)
        {
            if(gridMap[i][j] == 1)
            {
                W[wallCount].wallInit(M->getGridSize(),"images/wall.png");
                W[wallCount].placeWall(j + 1, gridSizeY - i);
                wallCount++;
            }
            else if(gridMap[i][j] == 2)
            {
                E[enemyCount].initEnm(M->getGridSize(),4,"images/e.png");
                E[enemyCount].placeEnemy(j + 1, gridSizeY - i);
                enemyCount++;
//                cout << E[enemyCount].getEnemyLoc().x << "    " << E[enemyCount].getEnemyLoc().y << endl;
            }
            else if(gridMap[i][j] == 3)
            {
                P->initPlayer(M->getGridSize(),"images/p.png");
                P->loadArrowImage("images/arr.png");
                P->placePlayer(j + 1, gridSizeY - i);
                collision->UpdatePlayerPosition(i, j);
//                cout << P->getPlayerLoc().x << "    " << P->getPlayerLoc().y << endl;
            }
            else if(gridMap[i][j] == 4)
            {
                M->loadBackgroundImage("images/bak.jpg");
                M->loadChestImage("images/chest.png");
                M->placeChest(j + 1, gridSizeY - i);
            }
            else if(gridMap[i][j] == 5)
            {
                M->loadSetOfArrowsImage("images/arrwset.png");
                M->placeStArrws(j + 1, gridSizeY - i);
            }
        }
    }


//    for(int i=1; i< M->getGridSize();i++)
//    {
//      W[i].wallInit(M->getGridSize(),"images/wall.png");
//      W[i].placeWall(i,5);
//    }
//
//
//    for(int i=0; i<10;i++)
//    {
//        E[i].initEnm(M->getGridSize(),4,"images/e.png");
//        E[i].placeEnemy(float(rand()%(M->getGridSize())),float(rand()%(M->getGridSize())));
//    }
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

        glPushMatrix();
         M->drawBackground();
        glPopMatrix();


        for(int i=0; i  < wallCount;i++)
        {
           W[i].drawWall();
        }

        glPushMatrix();
            M->drawGrid();
        glPopMatrix();

        glPushMatrix();
            P->drawplayer();
        glPopMatrix();

        for(int i=0; i<10;i++)
        {
        E[i].drawEnemy();
        }

        glPushMatrix();
            P->drawArrow();
        glPopMatrix();

         glPushMatrix();
           M->drawChest();
        glPopMatrix();

        glPushMatrix();
           M->drawArrows();
        glPopMatrix();

    glutSwapBuffers();
}




void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
             P->shootArrow();
        break;
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}


 void GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    xPos =posX ;
    yPos =posY ;
}

 void idle(void)
{

    //Your Code here

    glutPostRedisplay();
}


void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
            }
            break;


      case GLUT_RIGHT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
            }
            break;
    }
     glutPostRedisplay();
};

void Specialkeys(int key, int x, int y)
{

    // Your Code here
    switch(key)
    {
    case GLUT_KEY_UP:
         P->movePlayer("up",P->frames);
         E[0].moveEnemy("up");
         E[1].moveEnemy("up");
         E[2].moveEnemy("up");
    break;

    case GLUT_KEY_DOWN:
         P->movePlayer("down",P->frames);
         E[0].moveEnemy("down");
         E[1].moveEnemy("down");
         E[2].moveEnemy("down");
    break;

    case GLUT_KEY_LEFT:
         P->movePlayer("left",P->frames);
         E[0].moveEnemy("left");
         E[1].moveEnemy("left");
         E[2].moveEnemy("left");

    break;

    case GLUT_KEY_RIGHT:
         P->movePlayer("right",P->frames);
         E[0].moveEnemy("right");
         E[1].moveEnemy("right");
         E[2].moveEnemy("right");
    break;

   }
  glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init();

   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

   return EXIT_SUCCESS;
}
