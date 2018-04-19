// updated 2/7/18

#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h>
#include <glut.h>
#include <iostream>
#include <vector>
#include <Model.h>
#include <Inputs.h>
#include <unordered_map>
#include <AudioSource.h>
#include <AudioEngine.h>
#include <DeltaTime.h>
#include <Player.h>
#include <Grid.h>
#include <fstream>

using namespace std;

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        int windowsMsg(HWND, UINT, WPARAM, LPARAM);

        WPARAM wParam;
        float screenHeight, screenWidth;

        static vector<Model*> movableObjects; // only moving objects will check for collision
        static vector<Model*> staticObjects; // environmental, non-moving objects don't need to check for collision
        static vector<Model*> enemies;

        static Grid* grid;

        static Inputs *keyboardAndMouse;

    protected:
        unordered_map<string, AudioSource*> audioSources;
        Player* player;
        AudioEngine* audioEngine;
        bool isLoaded;
        AudioSource* BGM;


    private:

        void GenerateGrid();

        DeltaTime* dTime;

        int gridSizeX, gridSizeY;
        string mapFilePath;



        vector<vector<int>> gridMap;
//        Enemy* testEnemy;
};

#endif // GLSCENE_H
